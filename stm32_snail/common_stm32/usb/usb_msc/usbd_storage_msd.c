/**
  ******************************************************************************
  * @file    usbd_storage_msd.c
  * @author  MCD application Team
  * @version V1.2.0
  * @date    09-November-2015
  * @brief   This file provides the disk operations functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc_mem.h"
#include "rook_sd.h"
#include "my_misc.h"

#define STORAGE_LUN_NBR                  1 
/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata[] = {//36
  
  /* LUN 0 */
  0x00,		
  0x80,		
  0x02,		
  0x02,
  (USBD_STD_INQUIRY_LENGTH - 5),
  0x00,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'm', 'i', 'c', 'r', 'o', 'S', 'D', ' ', /* Product      : 16 Bytes */
  'F', 'l', 'a', 's', 'h', ' ', ' ', ' ',
  '1', '.', '0' ,'0',                     /* Version      : 4 Bytes */
}; 

/**
  * @}
  */ 


/** @defgroup STORAGE_Private_FunctionPrototypes
  * @{
  */ 
int8_t STORAGE_Init (uint8_t lun);

int8_t STORAGE_GetCapacity (uint8_t lun, 
                           uint32_t *block_num, 
                           uint32_t *block_size);

int8_t  STORAGE_IsReady (uint8_t lun);

int8_t  STORAGE_IsWriteProtected (uint8_t lun);

int8_t STORAGE_Read (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_Write (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_GetMaxLun (void);


USBD_STORAGE_cb_TypeDef USBD_MICRO_SDIO_fops =
{
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  (int8_t *)STORAGE_Inquirydata,
};

USBD_STORAGE_cb_TypeDef  *USBD_STORAGE_fops = &USBD_MICRO_SDIO_fops;
////#ifndef USE_STM3210C_EVAL   
////extern SD_CardInfo SDCardInfo;
////#endif
__IO uint32_t count = 0;


/**
  * @brief  Initialize the storage medium
  * @param  lun : logical unit number
  * @retval Status
  */

int8_t STORAGE_Init (uint8_t lun)
{
  return (0);
  
}

/**
  * @brief  return medium capacity and block size
  * @param  lun : logical unit number
  * @param  block_num :  number of physical block
  * @param  block_size : size of a physical block
  * @retval Status
  */
int8_t STORAGE_GetCapacity (uint8_t lun, uint32_t *block_num, uint32_t *block_size)
{
#if 0 
#ifdef USE_STM3210C_EVAL   
  SD_CardInfo SDCardInfo;
  
  SD_GetCardInfo(&SDCardInfo);  
  
#else
  if(SD_GetStatus() != 0 )
  {
    return (-1); 
  }   
#endif  
#endif
  SD_CardInfo SDCardInfo;
  
  SD_GetCardInfo(&SDCardInfo);  
  
  *block_size =  512;  
  *block_num =  SDCardInfo.CardCapacity / 512;  
  return (0);
  
}

/**
  * @brief  check whether the medium is ready
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t  STORAGE_IsReady (uint8_t lun)
{
#if 0 
#ifndef USE_STM3210C_EVAL  
  
  static int8_t last_status = 0;

  if(last_status  < 0)
  {
    SD_Init();
    last_status = 0;
  }
  
  if(SD_GetStatus() != 0)
  {
    last_status = -1;
    return (-1); 
  }  
#else
  if( SD_Init() != 0)
  {
    return (-1);
  }  
#endif
#endif  
  return (0);
}

/**
  * @brief  check whether the medium is write-protected
  * @param  lun : logical unit number
  * @retval Status
  */
int8_t  STORAGE_IsWriteProtected (uint8_t lun)
{
  return  0;
}

/**
  * @brief  Read data from the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to save data
  * @param  blk_addr :  address of 1st block to be read
  * @param  blk_len : nmber of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Read (uint8_t lun, 
                 uint8_t *buf, 
                 uint32_t blk_addr,                       
                 uint16_t blk_len)
{
///int ii;  
 if(SD_ReadSector(blk_addr, buf, blk_len)==0)
///  return 0;
///else
  return -1;
#if 0
  _printk("\n blk[%d]:",blk_addr);  
for(ii=0;ii<64;ii++)
{
_printk(" [%x]",*(buf+ii));  
}
  _printk("\n ");  
#endif
  return 0;
}
/**
  * @brief  Write data to the medium
  * @param  lun : logical unit number
  * @param  buf : Pointer to the buffer to write from
  * @param  blk_addr :  address of 1st block to be written
  * @param  blk_len : nmber of blocks to be read
  * @retval Status
  */
int8_t STORAGE_Write (uint8_t lun, 
                  uint8_t *buf, 
                  uint32_t blk_addr,
                  uint16_t blk_len)
{
if(SD_WriteSector(blk_addr, buf, blk_len)==0) 
///  return 0;
///else
  return -1;
#if 0  
  if( SD_WriteMultiBlocks (buf, 
                           blk_addr * 512, 
                           512,
                           blk_len) != 0)
  {
    return -1;
  }
#endif
#if 0  
#ifndef USE_STM3210C_EVAL  
  SD_WaitWriteOperation();
  while (SD_GetStatus() != SD_TRANSFER_OK);  
#endif  
#endif  
  
  return (0);
}

/**
  * @brief  Return number of supported logical unit
  * @param  None
  * @retval number of logical unit
  */

int8_t STORAGE_GetMaxLun (void)
{
  return (STORAGE_LUN_NBR - 1);
///  return (STORAGE_LUN_NBR );
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

