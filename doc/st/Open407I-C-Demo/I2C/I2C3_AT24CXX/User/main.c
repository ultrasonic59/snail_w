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
#include "24C02.h"
#include <string.h>
#include <stdio.h>


/* Private function prototypes -----------------------------------------------*/
void  Delay(uint32_t nCount);
void GPIO_Configuration(void);


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	uint16_t Addr;
	uint8_t WriteBuffer[256],ReadBuffer[256];
	
	USART_Configuration();
	I2C_Configuration();
	
	printf("\r\n****************************************************************\r\n");
	
	for(Addr=0; Addr<256; Addr++)
	WriteBuffer[Addr]=Addr;	 /* 填充WriteBuffer */
	
	/* 开始向EEPROM写数据 */
	printf("\r\n EEPROM 24C02 Write Test \r\n");
	I2C_Write(Open_I2Cx,ADDR_24LC02,0,WriteBuffer,sizeof(WriteBuffer) );
	printf("\r\n EEPROM 24C02 Write Test OK \r\n");
	
	/* EEPROM读数据 */
	printf("\r\n EEPROM 24C02 Read Test \r\n");
	I2C_Read(Open_I2Cx,ADDR_24LC02,0,ReadBuffer,sizeof(WriteBuffer) );
	
	if(memcmp(WriteBuffer,ReadBuffer,sizeof(WriteBuffer)) == 0 ) /* 匹配数据 */
		printf("\r\n EEPROM 24C02 Read Test OK\r\n");
	else
		printf("\r\n EEPROM 24C02 Read Test False\r\n");
	
	/* Infinite loop */

	while (1)
	{
	
	}
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
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
