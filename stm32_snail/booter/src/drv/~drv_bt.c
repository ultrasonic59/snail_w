 #include <string.h>
 #include <stdio.h>
#include "stm32f2xx.h"
///#include "rtthread.h"
///#include <drivers/spi.h>
#include "types.h"
#include "drv_utrk.h"
#include "defectoscope.h"
#include "drv_bt.h"
#include "platform.h"
///#include <rthw.h>
///#include <rtthread.h>
///#include <rtdevice.h>
///#include "drivers/serial.h"
///+++++++++++++++++++++++
#define NUM_SPD_BT	5

const u8 tbl_bt_br[NUM_SPD_BT]={0,2,4,6,7};
const u32 bt_uart_br[] = {			// 
						BAUD_RATE_9600,			// 
						BAUD_RATE_14400,		// 
						BAUD_RATE_19200,		// 
						BAUD_RATE_28800,		// 
						BAUD_RATE_38400,		// 
						BAUD_RATE_56000,		// 
						BAUD_RATE_57600,		// 
						BAUD_RATE_115200,		// 
						BAUD_RATE_128000, 	//	
						BAUD_RATE_256000		//	
};

////rt_device_t uart4_id;

///+++++++++++++++++++++++
extern void  on_irq_bt_rx(void);
extern void  off_irq_bt_rx(void);
/*
void  on_irq_bt_rx(void)
{
  
}
void  off_irq_bt_rx(void)
{
}
*/
u8 is_irq_bt_rx_on(void)
{
return 0;
}
void set_bt_uart_br(u32 br)
{
uint32_t tmpreg = 0x00;
uint32_t apbclock = 0x00;
uint32_t integerdivider = 0x00;
uint32_t fractionaldivider = 0x00;
RCC_ClocksTypeDef RCC_ClocksStatus;

RCC_GetClocksFreq(&RCC_ClocksStatus);
apbclock = RCC_ClocksStatus.PCLK1_Frequency;
integerdivider = ((25 * apbclock) / (4 * br));    
tmpreg = (integerdivider / 100) << 4;
fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
UART_BT->BRR = (uint16_t)tmpreg;
}
extern int send_char_bt(u8 data);
/*
int send_char_bt(u8 data)
{
u8 btst=data;	
////if(	uart4_id)
////	rt_device_write(uart4_id,0,	&btst,1);
return 0;	
}
*/

int send_bt_string(char *buff)
{
u8 ii;
int rez=0;
///taskENTER_CRITICAL();
if(buff==NULL)
	rez = -1;
else
	{	
for(ii=0;ii<MAX_LEN_STR_BT;ii++)
	{
	if(buff[ii]!= 0)
		{
		if(send_char_bt(buff[ii])<0)
			{
			rez= -2;
			}
		else
			{
			rez++;
			}	
		}
	else
		break;
	}
	}	
////taskEXIT_CRITICAL();
return rez;	
}
extern int uart_bt_rx_rdy(void);
/*
int uart_bt_rx_rdy(void)
{
u32 ready_flg;
#if 0
if(	uart4_id)
	{
	if(rt_device_control(uart4_id,RT_DEVICE_GET_LEN, (void*)&ready_flg)==RT_EOK)
	{
	if(	ready_flg)
		return 1;
	else
		return 0;
	}
	else 
			return 0;
	}
else 
#endif
	return 0;	
}
*/
extern int uart_bt_read(u8* o_ch, int cnt);

int check_connect_bt_spd(u32 br)
{
///int ii;	
u32 t_cur_tick;
u32 t_last_tick;
u8 ch;
u8 rsv_ok=0;
u8 flg_irq_bt_rx_on = 0;
////reset_bt();

///taskENTER_CRITICAL();
/*	
if (is_irq_bt_rx_on())
	{
	off_irq_bt_rx();
	flg_irq_bt_rx_on = 1;
	}
*/
set_bt_uart_br(br);
send_bt_string("AT");
t_cur_tick=mico_get_time();
for(;;)
	{
	if(uart_bt_rx_rdy()	)
		{
//////		rt_device_read(uart4_id,0,	&ch,1);
		uart_bt_read(&ch,1);	
///		ch=h_bt_uart_dat;
		debug_out("\n %c[%x]",ch,ch);
		if(ch=='O')
			rsv_ok=1;	
		else
			rsv_ok=0;	
		break;
		}
	else
		{
		t_last_tick=mico_get_time();
		if((t_last_tick-t_cur_tick)>TIME_WAIT_BT)
			{
			rsv_ok=0;	
			break;
			}	
		}	
	}
if(rsv_ok)
	{
for(;;)
	{
	if(uart_bt_rx_rdy()	)
		{
////		rt_device_read(uart4_id,0,	&ch,1);
/////		rt_kprintf("\n %c[%x]",ch,ch);
		uart_bt_read(&ch,1);	
		debug_out("\n %c[%x]",ch,ch);
		if(ch=='K')
			rsv_ok=1;	
		else
			rsv_ok=0;	
		break;
		}
	else
		{
		t_last_tick=mico_get_time();
		if((t_last_tick-t_cur_tick)>TIME_WAIT_BT)
			{
			rsv_ok=0;	
			break;
			}	
		}	
	}
	}
///taskEXIT_CRITICAL();
if (flg_irq_bt_rx_on)
	on_irq_bt_rx();

if(rsv_ok)
	return TRUE;
else
	return FALSE;
}

void on_pow_bt(u8 on_off)
{
if(on_off&0x1)
	wr_dat_addr(ADDR_UPR_BT,0x03);
else
wr_dat_addr(ADDR_UPR_BT,0x2);
	
}
void reset_bt(void)
{
wr_dat_addr(ADDR_UPR_BT,0x1);
uDelay(10000);
wr_dat_addr(ADDR_UPR_BT,0x03);
}

u16 check_connect_bt(void)
{
u8 ii;	
///reset_bt();
////on_pow_bt(1);	
	
////check_connect_bt_spd(1)	;
	
for(ii=NUM_SPD_BT;ii>0;ii--)
	{
	if(check_connect_bt_spd(bt_uart_br[tbl_bt_br[ii-1]]))
		{
		return 	bt_uart_br[tbl_bt_br[ii-1]];
		}	
	}

return 0;
}
void set_br_bt(u32 br_div) 
{
if(br_div==BAUD_RATE_9600)
	{
	send_bt_string("AT+BAUD4");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_9600);
	}	
else if(br_div==BAUD_RATE_19200)
	{
	send_bt_string("AT+BAUD5");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_19200);
	}	
else if(br_div==BAUD_RATE_38400)
	{
	send_bt_string("AT+BAUD6");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_38400);
	}	
else if(br_div==BAUD_RATE_57600)
	{
	send_bt_string("AT+BAUD7");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_57600);
	}	
else if(br_div==BAUD_RATE_115200)
	{
	send_bt_string("AT+BAUD8");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_115200);
	}	
else 
	{
	send_bt_string("AT+BAUD4");
	uDelay(10000);	
	set_bt_uart_br(BAUD_RATE_9600);
	}	
}

void set_name_bt(char *iname)
{
int rez;	
char t_name[26];
sprintf(t_name,"AT+NAME%s",iname);
rez=send_bt_string(t_name);
debug_out("\n [%d]%s",rez,t_name);
msleep(BT_CMD_DELAY);

}
void set_pincode_bt(int pin_code)
{
char t_name[26];
sprintf(t_name,"AT+PIN%04d",pin_code);
send_bt_string(t_name);
debug_out("\n %s",t_name);
msleep(BT_CMD_DELAY);
}

int pairing(void)
{
u32 t_spd_dev;
u16 t_num_dev;
char t_name[26];
///reset_bt();
t_spd_dev=check_connect_bt();
debug_out("\npairing[%d]",t_spd_dev);
if(t_spd_dev==0)
	return FALSE;	
////t_num_dev=(u16)sysPar.NumDev;
t_num_dev=9;
sprintf(t_name,"velograph_%d",t_num_dev);
set_name_bt(t_name);
///set_pincode_bt(7777);
set_pincode_bt(t_num_dev);
if(t_spd_dev!=DEF_BT_BR)
	set_br_bt(DEF_BT_BR);
return TRUE;	
	
}
///========================================

void init_bt(void)
{		
#if 0	
if(!extraPar.on_bt)
	{
	printf("\n ++++ bluetooth off ++++");
	printf("\n push any key ");
	getchar();	
	clr_sc(CLR_ALL);
	return;
	}
#endif	
if(pairing())
	{
	debug_out("[ok]");
	}
else
	{
	debug_out("[bad]");
	}
debug_out("\n push any key ");
}
///+++++++++++++++++++++++
