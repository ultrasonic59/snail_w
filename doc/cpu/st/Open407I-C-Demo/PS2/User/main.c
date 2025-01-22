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
#include "usart.h"
#include "PS2.h"

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



int main(void)
{
    uint8_t count=0;
	uint8_t data=0;

	GPIO_Configuration();	
	USART_Configuration();
	USART_NVIC_Config();

	printf("\r\nWelcome to WaveShare STM32F4 series MCU Board Open407I\r\n");
	printf("\r\n*****************Now the PS2 experiments**************\r\n");
	printf("\r\nPress the button on the PS2:\r\n");
	
	PS2_Init();
    while (1)
    {
		data = PS2_Test();
		if(data!=0xff)
		{
			printf("Keyboard Input : %c\r\n",data);
	        if(count>=2)
	        {
				count=0;
				GPIO_ResetBits(LED1_Port , LED1_Pin);
				GPIO_ResetBits(LED2_Port , LED2_Pin);
				GPIO_ResetBits(LED3_Port , LED3_Pin);
				GPIO_ResetBits(LED4_Port , LED4_Pin);
	        }
	        else
	        {
				GPIO_SetBits(LED1_Port , LED1_Pin);
				GPIO_SetBits(LED2_Port , LED2_Pin);
				GPIO_SetBits(LED3_Port , LED3_Pin);
				GPIO_SetBits(LED4_Port , LED4_Pin);
	        }
		}
	}

}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
