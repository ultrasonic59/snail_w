///#include "menu.h"
#include <stdint.h>
#include <misc.h>

#include "types.h"
#include "board.h"
#include "flash_if.h"
#include "printk.h"
///#include "common.h"

///extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;
extern uint32_t FLASH_If_Erase(uint32_t StartAddr,uint32_t EndAddr);
uint32_t jumpAddress;
pFunction Jump_To_Application;
///============================================
////__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;
///============================================
#ifdef USE_FULL_ASSERT
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
///=====================================
uint32_t programBytesToRead;
uint32_t programBytesCounter;
uint32_t currentAddress;
uint32_t readBytes;
uint8_t readBuffer[512];
extern void hw_board_init(void);
extern void wait_config_fpga(void);
extern void uDelay (const uint32_t usec);

int main(void)
{ 
///uint32_t ii;	
///uint32_t end_flash_addr=0;	

///uint32_t tst;	
hw_board_init()	;
////uDelay(10000);	
///UART_BT_Init(); 
printk("\r\n Start Boot\r\n");	
	
#if 0
for(ii=0;ii<10;ii++)	
	{
	uDelay(20000);	///200ms
	}
printk("[OK] \n ");  
#endif
///==============================	
/*	
  USBD_Init(&USB_OTG_dev,
            USB_OTG_HS_CORE_ID,
            &USR_desc, 
            &USBD_HID_cb, 
            &USR_cb);
	*/
///=================================	

    __disable_irq();
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, MAIN_PROGRAM_START_ADDRESS);
      
    jumpAddress = *(__IO uint32_t*) (MAIN_PROGRAM_START_ADDRESS + 4);
///     jumpAddress = (MAIN_PROGRAM_START_ADDRESS + 4);
    printk(" Jamp addres=[%x:%x]\r\n",jumpAddress,MAIN_PROGRAM_START_ADDRESS);	

    Jump_To_Application = (pFunction) jumpAddress;
    __set_MSP(*(__IO uint32_t*) MAIN_PROGRAM_START_ADDRESS);
    Jump_To_Application();
///=============================================
	
for(;;)
{
  ;
}
  
  return 0;
} 

