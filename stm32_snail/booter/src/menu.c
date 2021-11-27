/**
  ******************************************************************************
  * @file    STM32F2xx_IAP/src/menu.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    02-May-2011
  * @brief   This file provides the software which contains the main menu routine.
  *          The main menu gives the options of:
  *             - downloading a new binary file, 
  *             - uploading internal flash memory,
  *             - executing the binary file already loaded 
  *             - disabling the write protection of the Flash sectors where the 
  *               user loads his binary file.
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

/** @addtogroup STM32F2xx_IAP
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "flash_if.h"
#include "menu.h"
#include "ymodem.h"

#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern pFunction Jump_To_Application;
uint32_t JumpAddress;
__IO uint32_t FlashProtection = 0;
uint8_t tab_1024[1024] =
  {
    0
  };
uint8_t FileName[FILE_NAME_LENGTH];

/* Private function prototypes -----------------------------------------------*/
void SerialDownload(void);
void SerialUpload(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(void)
{
  uint8_t Number[10] = "          ";
  int32_t Size = 0;

  SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  Size = Ymodem_Receive(&tab_1024[0]);
  if (Size > 0)
  {
    SerialPutString("\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
    SerialPutString(FileName);
    Int2Str(Number, Size);
    SerialPutString("\n\r Size: ");
    SerialPutString(Number);
    SerialPutString(" Bytes\r\n");
    SerialPutString("-------------------\n");
  }
  else if (Size == -1)
  {
    SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
  }
  else if (Size == -2)
  {
    SerialPutString("\n\n\rVerification failed!\n\r");
  }
  else if (Size == -3)
  {
    SerialPutString("\r\n\nAborted by user.\n\r");
  }
  else
  {
    SerialPutString("\n\rFailed to receive the file!\n\r");
  }
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(void)
{
  uint8_t status = 0 ; 

  SerialPutString("\n\n\rSelect Receive File\n\r");

  if (GetKey() == CRC16)
  {
    /* Transmit the flash image through ymodem protocol */
    status = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);

    if (status != 0) 
    {
      SerialPutString("\n\rError Occurred while Transmitting File\n\r");
    }
    else
    {
      SerialPutString("\n\rFile uploaded successfully \n\r");
    }
  }
}

u32 check_noise (void)
{
	const u8 pwd[] = "1234";
	u32 pwd_cnt = 0;
	u8 ch;
	u32 ret_cnt = 32;
	u32 ret = 0;

	SerialPutString("\r\nInput password 1234 to prove you're not noise: ");

	myGetKey_flush();
	while (myGetKey(&ch) && ret_cnt--)
	{
		if (pwd[pwd_cnt] == ch)
		{
			if (++pwd_cnt >= strlen((const char*)pwd))
			{
				SerialPutString("\r\nOK. Enter command: ");
				ret = 1;
				break;
			}
		}
		else
			pwd_cnt = 0;
	}

	return ret;
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
  uint8_t key = 0;

  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n=              (C) COPYRIGHT 2011 STMicroelectronics                 =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=  STM32F2xx In-Application Programming Application  (Version 1.0.0) =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=                                   By MCD Application Team          =");
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n\r\n");

  /* Test if any sector of Flash memory where user application will be loaded is write protected */
  if (FLASH_If_GetWriteProtectionStatus() == 0)   
  {
    FlashProtection = 1;
  }
  else
  {
    FlashProtection = 0;
  }

  while (1)
  {
    SerialPutString("\r\n================== Main Menu ============================\r\n\n");
    SerialPutString("  Download Image To the STM32F2xx Internal Flash ------- 1\r\n\n");
    SerialPutString("  Upload Image From the STM32F2xx Internal Flash ------- 2\r\n\n");
    SerialPutString("  Execute The New Program ------------------------------ 3\r\n\n");

    if(FlashProtection != 0)
    {
      SerialPutString("  Disable the write protection ------------------------- 4\r\n\n");
    }

    SerialPutString("==========================================================\r\n\n");

    /* Receive key */
	if (check_noise())
	{
		myGetKey_flush();
    	if (myGetKey(&key) == 0)
			key = 0x33;
	}
	else
		key = 0x33;

    if (key == 0x31)
    {
      /* Download user application in the Flash */
      SerialDownload();
    }
    else if (key == 0x32)
    {
      /* Upload user application from the Flash */
	  SerialPutString("\r\nThis command is disabled. ");
      //SerialUpload();
    }
    else if (key == 0x33) /* execute the new program */
    {
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      /* Jump to user application */
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      Jump_To_Application();
    }
    else if ((key == 0x34) && (FlashProtection == 1))
    {
      /* Disable the write protection */
      switch (FLASH_If_DisableWriteProtection())
      {
        case 1:
        {
          SerialPutString("Write Protection disabled...\r\n");
          FlashProtection = 0;
          break;
        }
        case 2:
        {
          SerialPutString("Error: Flash write unprotection failed...\r\n");
          break;
        }
        default:
        {
        }
      }
    }
    else
    {
      if (FlashProtection == 0)
      {
        SerialPutString("Invalid Number ! ==> The number should be either 1, 2 or 3\r");
      }
      else
      {
        SerialPutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
      }
    }
  }
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/