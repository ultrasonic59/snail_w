#include <stdio.h>
#include <efxinc.h>

#include "misc.h"
#include "f1c100s_gpio.h"
#include "f1c100s-irq.h"
extern uint32_t get_en_intc(uint8_t num);
extern uint32_t get_mask_intc(uint8_t num);


void print_int_mask()
{
	uint32_t tmp;
printf("\r\n====print_int_mask======");
tmp= get_en_intc(0);
printf("\r\n====INTC_EN_REG[0][%08x]======",tmp);
tmp= get_en_intc(1);
printf("\r\n====INTC_EN_REG[1][%08x]======",tmp);
tmp= get_mask_intc(0);
printf("\r\n====INTC_MASK_REG[0][%08x]======",tmp);
tmp= get_mask_intc(1);
printf("\r\n====INTC_MASK_REG[1][%08x]======",tmp);
	
}
void obr_cmd(char ikey)
{
switch(ikey)
	{
	case 'a':
		print_int_mask();
		break;
	default:
		break;
	}	
}



void test_thr(void)
{
char tkey;
uint8_t btst=0;	
////uint8_t btst1=0;	

printf("\r\n====test_thr======");
#if 0	
for(;;)
	{
		btst1=check_key();
		put_test1_pin(btst)	;
		btst++;
		printf("\r\n[%x][%x]",btst,btst1);
		sys_delay(10);
		
	}	
	#endif
for(;;)
	{
	if(check_key())
		{
		tkey=sys_uart_getc();
			obr_cmd(tkey);
	////	printf("pushed key[%x]",tkey);
		}
	else
		{
	////	put_test1_pin(btst)	;
	////	btst++;
		sys_delay(10);

		}
	}
}

void init_test1_pin(void)
{
gpio_pin_init(TEST1_PORT, TEST1_PIN, GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_DRV_3);
}
void put_test1_pin(uint8_t idat)
{
if(idat&0x1)
	gpio_pin_set(TEST1_PORT, TEST1_PIN);
else
	gpio_pin_clear(TEST1_PORT, TEST1_PIN);
	
}
