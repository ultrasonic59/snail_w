/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "config.h"
#include "usart.h"
#include "ws_AT45DBXX.h"
#include <string.h>
#include <stdio.h>

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

/* Private define ------------------------------------------------------------*/
#define LED1_Port						GPIOH
#define LED1_Pin						GPIO_Pin_2
#define LED1_RCC_AHBPeriph				RCC_AHB1Periph_GPIOH

#define LED2_Port						GPIOH
#define LED2_Pin						GPIO_Pin_3
#define LED2_RCC_AHBPeriph				RCC_AHB1Periph_GPIOH

#define LED3_Port						GPIOI
#define LED3_Pin						GPIO_Pin_8
#define LED3_RCC_AHBPeriph				RCC_AHB1Periph_GPIOI

#define LED4_Port						GPIOI
#define LED4_Pin						GPIO_Pin_10
#define LED4_RCC_AHBPeriph				RCC_AHB1Periph_GPIOI
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */
	u8 num=0;
	u8 ID[4];
	u8 tmp;
 

	GPIO_Configuration();	
	USART_Configuration();
	//USART_NVIC_Config();
	printf("\r\nWelcome to WaveShare STM32F4 series MCU Board Open407V-D\r\n");

	AT45DBXX_Init();
	printf("AT45DBXX had been Init!\r\n");
	AT45DBXX_Read_ID(ID);
	printf("AT45DBXX ID is");
	for(num=0;num<4;num++)
	{
		printf(" 0x%x ",ID[num]);
	}
	printf("\r\n");

	printf("\r\nFALSH AT45DBXX Write Test: \r\n");
	for(num=0;num<255;num++) /*Written to the flash*/
	{
		write_buffer((u16)num,num);
		printf("%3d ",num);
	}

	printf("\r\nFALSH AT45DBXX Read Test: \r\n");

	for(num=0;num<255;num++) /*Read the flash*/
	{
		tmp=read_buffer((u16)num);
		printf("%3d ",tmp);
	}

	while (1)
	{
		GPIO_SetBits(LED1_Port , LED1_Pin);
		GPIO_SetBits(LED2_Port , LED2_Pin);
		GPIO_SetBits(LED3_Port , LED3_Pin);
		GPIO_SetBits(LED4_Port , LED4_Pin);
		Delay(0x1fffff);
		GPIO_ResetBits(LED1_Port , LED1_Pin);
		GPIO_ResetBits(LED2_Port , LED2_Pin);
		GPIO_ResetBits(LED3_Port , LED3_Pin);
		GPIO_ResetBits(LED4_Port , LED4_Pin);
		Delay(0x1fffff);
	}
}
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOF Periph clock enable */
	RCC_AHB1PeriphClockCmd(LED1_RCC_AHBPeriph | LED2_RCC_AHBPeriph | LED3_RCC_AHBPeriph | LED4_RCC_AHBPeriph, ENABLE);
	
	/* Configure PF6 PF7 PF8 PF9 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = LED1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(LED1_Port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2_Pin;
	GPIO_Init(LED2_Port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED3_Pin;
	GPIO_Init(LED3_Port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED4_Pin;
	GPIO_Init(LED4_Port, &GPIO_InitStructure);
}
/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {

  }
}

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

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
