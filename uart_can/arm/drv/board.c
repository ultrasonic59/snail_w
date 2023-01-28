#include <stdio.h>
#include <string.h>

#include "board.h"
#include "serial.h"
#include "my_misc.h"

void init_gpio(void)
{
////RCC_AHBPeriphClockCmd(XEN_PIN_RCC_AHB,ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
  
////=========== MY_UART =================================================== 
RCC_APB2PeriphClockCmd(MY_UART_GPIO_RCC, ENABLE);
GPIO_InitStructure.GPIO_Pin = MY_UART_TX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_Init( MY_UART_TX_GPIO, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Pin = MY_UART_RX_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;////GPIO_Mode_AF_PP;
GPIO_Init( MY_UART_RX_GPIO, &GPIO_InitStructure );
  
////GPIO_PinAFConfig(UART_DBG_TX_GPIO_PORT, UART_DBG_TX_PIN_NPIN, UART_DBG_TX_AF);
////GPIO_PinAFConfig(UART_DBG_RX_GPIO_PORT, UART_DBG_RX_PIN_NPIN, UART_DBG_RX_AF);
////============ CAN ===============================================
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
RCC_APB2PeriphClockCmd(CAN_GPIO_PORT_RCC, ENABLE);

/// ==============CAN RX  pins =============================
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
////   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);
//// GPIO_PinRemapConfig(GPIO_Remap1_CAN, ENABLE);
  
/// ==============CAN  TX pins =============================
////GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
 GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);
 ///============ LED ================== 
GPIO_InitStructure.GPIO_Pin = LED_PIN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init( LED_PIN_GPIO, &GPIO_InitStructure );
}
static uint8_t st_led=0;
int led_time=0;
#define LED_TIME 100
void vApplicationTickHook( void )
{
if(led_time) 
  {
  led_time--;
  if(st_led==0)
    {
    st_led=1;
    put_led(st_led);
    }
  }
else if(st_led!=0)
    {
    st_led=0;
    put_led(st_led);
    }
}
void on_led(void)
{
 led_time= LED_TIME;
 st_led=0;
}

void  put_led(uint8_t idat)
{
if(idat&0x1)  
  GPIO_WriteBit(LED_PIN_GPIO,LED_PIN,(BitAction)(0)); 
else
  GPIO_WriteBit(LED_PIN_GPIO,LED_PIN,(BitAction)(0x1)); 
}

void board_init(void)
{
init_gpio();
///init_serial();
usart_setup();

cur_can_br=DEF_CAN_BR;

init_can();
put_led(0); ///off led
}
void uDelay (const uint32_t usec)
{
uint32_t count = 0;
const uint32_t utime = 45*usec;////(120 * usec / 7);
do
  {
   if ( ++count > utime )
    {
    return ;
    }
  }
while (1);
}
////======================================================
volatile unsigned int counter;
volatile uint8_t status;
volatile uint8_t commands_pending;
uint8_t d_data[MAX_CAN_LEN];

void testTask( void *pvParameters )
{
uint8_t t_tst=1;  
////put_led(t_tst);
////uint8_t test_data[8]={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};

for( ;; )
  {
  t_tst++; 
 //// write_my_uart( (char*)&t_tst,1) ;
       sendchar_my_uart(0x35) ; 
         vTaskDelay(200);
  ////       put_led(t_tst);
 ////       CanWriteData(0xA5,test_data,8);
//// slcan_command();
  }
  
}

