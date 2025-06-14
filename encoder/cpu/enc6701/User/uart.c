#include <string.h>
////#include <stdio.h>
#include "uart.h"
#include "../brd/enc6701_brd.h"
///#include "my_misc.h"

volatile uint8_t rx_buff_ready=0;
static uint8_t rx_buff[LEN_RX_BUFF];
static uint8_t len_rx_dat=0;
uart_cmd_t rx_cmd;
uart_cmd_t tx_cmd;
////===================================
void uart1_rx_handler(void)
{
uint8_t tdat;  
////if(UART1->SR &UART1_FLAG_RXNE)
{
  tdat=(uint8_t)USART1->DATAR;
  if(tdat=='\0'){
    if(len_rx_dat!=0){
      memcpy(rx_cmd.buff,rx_buff,len_rx_dat);
      rx_cmd.len=len_rx_dat;
      rx_buff_ready=1;
      len_rx_dat=0;
      }
    }
  else{
    if(len_rx_dat<LEN_RX_BUFF){
        rx_buff[len_rx_dat]= tdat;
        len_rx_dat++;
      }
    }
  }
}
///==========================================
int uart_put_byte(uint8_t idat) 
{
while((USART1->STATR &USART_FLAG_TXE)==0);
USART1->DATAR = idat;
return 0;
}
int send_dat(uint8_t i_dat)
{
USART1->DATAR = i_dat;
return 0;
}
////=================================================
void tx_send(uart_cmd_t *cmd)
{
uint8_t ii=0;
while(cmd->len)
  {
  uart_put_byte(cmd->buff[ii]) ;
  cmd->len--;
  ii++;
  };
}
volatile uint8_t v_tmp=0;
void obr_uart_cmd(uart_cmd_t *cmd)
{
#if 0
 //// int tmp;
////uint16_t rez=0;
uint16_t htmp;
uint8_t btmp;
///char tstr[32];
if(cmd->len==0)
  return ;
btmp= *cmd->buff;
v_tmp=btmp;
switch(btmp)
  {
  case PUT_VIBRO:
////    sscanf((const char*)(cmd->buff+1),"%d",&htmp);
    htmp=str_to_half((char*)(cmd->buff+1));
    set_vibro(htmp);
///    rez=0;
    break;
  case PUT_LEDS:
////    sscanf((const char*)(cmd->buff+1),"%x",&htmp);
 ////   htmp=str_to_byte((char*)(cmd->buff+1));
    htmp=char_to_hex(cmd->buff[1]);
    put_leds(htmp);
///    rez=0;
    break;
  case PUT_POW_GEN:
 ////   htmp=str_to_byte((char*)(cmd->buff+1));
    htmp=char_to_hex(cmd->buff[1]);
    onoff_pow_gen(htmp);
///    rez=0;
    break;
    case GET_VERS:
     tx_cmd.buff[0]=GET_VERS;
     
     strcpy((char*)&tx_cmd.buff[1],VERS);
  
     strcpy((char*)&tx_cmd.buff[1+strlen(VERS)],__DATE__);
     tx_cmd.len=strlen((char*)tx_cmd.buff)+1;
      break;
    case GET_BAT:
 ////   char ctmp[5];
 ///   sprintf((char*)buf,"%05d",v_bat);
    htmp=cur_adc_dat;
    tx_cmd.buff[0]=GET_BAT;
 ////   hex_half_to_str(htmp, (char*)&tx_cmd.buff[1]);
 ////   htmp=0x1234;
    hex_half_to_str(htmp, (char*)&tx_cmd.buff[1]);
    tx_cmd.buff[5]='\0';
    tx_cmd.len=6;
#if 0
    rez=adc_results[0];
    rez+=adc_results[0]>>1;
     sprintf((char*)buf,"%c%05d",GET_BAT,rez);
   rez=strlen((char*)buf)+1;
    }
#endif
    break;
  case GET_TEMP:
#if 0    
    tmp=conv_adc_temper(adc_results[1]);
      sprintf((char*)buf,"%c%d",GET_TEMP,tmp);
    rez=strlen((char*)buf)+1;
#endif
      break;
  default:
 ///   rez=0;
    break;
}
#endif
////return rez;
}
////=================================================

uint8_t uart_get_byte(void) 
{
while((USART1->STATR & USART_FLAG_RXNE)!=0);
return ((uint8_t)USART1->DATAR);
}
uint8_t get_dat(void)
{
  return (uint8_t )USART1->DATAR;
}

uint8_t rx_rdy(void)
{
uint8_t tmp;
tmp=USART1->STATR;
if(tmp&USART_FLAG_RXNE)
  return 1;
else if(tmp&USART_FLAG_ORE)
  return 1;
else
  return 0;

}
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
/*********************************************************************
 * @fn      USART1_IRQHandler
 *
 * @brief   This function handles USART3 global interrupt request.
 *
 * @return  none
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uart1_rx_handler();
     }
}

#if 0
void uart_init(void)
{
UART1_DeInit() ;
UART1_Init(UART_DEF_BR, UART1_WORDLENGTH_8D, 
           UART1_STOPBITS_1, UART1_PARITY_NO, 
           UART1_SYNCMODE_CLOCK_DISABLE ,
           UART1_MODE_TXRX_ENABLE);
UART1_Cmd( ENABLE);
UART1_ITConfig( UART1_IT_RXNE, ENABLE);

}
#endif
