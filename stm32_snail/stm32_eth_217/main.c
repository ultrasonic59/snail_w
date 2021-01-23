/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_conf.h"
#include "stm32f2x7_eth.h"
#include "stm32f2x7_eth_bsp.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lwip/tcpip.h"
#include "snail_spd_brd.h"
#include "printk.h"

#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 1 )

extern void LwIP_Init(void);
extern void udpecho_init(void);
extern void uart_dbg_init(void);
void ToggleLed3(void * pvParameters);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
////USART_InitTypeDef USART_InitStructure;
char Message[256];
/////static __IO uint32_t TimingDelay;
//extern  uint32_t 	ADCConvertedValue;

/* Private function prototypes -----------------------------------------------*/
void NVIC_Config(void);
////extern void DebugComPort_Init(void);

 /* Private functions ---------------------------------------------------------*/

int main(void)
{
//// uint8_t tst=0;
gpio_init();
////============================================
NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
////============================================
uart_dbg_init();
printk("\n\r == uart_dbg_init OK ==");  

////==============================
#if 0
for(;;)
{
put_led3(tst);
uDelay(1000);
tst++;
}
#endif
////==============================
CAN_Config();
#if 1
ETH_BSP_Config();
/* Initilaize the LwIP stack */
LwIP_Init();
  
  /* Http webserver Init */
////  httpd_init();
////  tcpecho_init();
  
  /* Initialize udp echo server */
  udpecho_init();
#ifdef USE_DHCP
  /* Start DHCPClient */
  xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
#endif
#endif  
    
  /* Start toogleLed4 task : Toggle LED4  every 250ms */
xTaskCreate(ToggleLed3, "LED3", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
  
  /* Start scheduler */
  vTaskStartScheduler();

  while (1)
  {
  ;
////   Delay(1000);
////   STM_EVAL_LEDToggle(LED1);
 ///  temp= (((3.3/4096)*(ADCConvertedValue))-0.76)/(0.0025);
 ////  USART3_SendString((char *)Message,sprintf(Message,"\n \r %.1f",temp));

  }
}
void ToggleLed3(void * pvParameters)
{
uint8_t tst=0;
printk("\n\r == ToggleLed3 task ==");  
  
for( ;; )
  {
  put_led3(tst);
  tst++;
  vTaskDelay(250);
  }
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
#if 0  
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EVAL_COM1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif  
}
#if 0
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

#endif


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

