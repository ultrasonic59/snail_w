/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "fsmc_SRAM.h"
#include <stdio.h>
#include "usart.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

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

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);


/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  GPIO_Configuration();
  USART_Configuration();

  printf("\r\n/**************************************************/\r\n");

  SRAM_TEST();
  /* Infinite loop */
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

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
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

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

