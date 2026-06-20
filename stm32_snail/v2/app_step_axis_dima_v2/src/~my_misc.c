#include <stdint.h>
#include "board.h"
#include "my_misc.h"

////#include <cmsis_iccarm.h>
#include "printk.h"
///=======================================================================
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
///=======================================================================

pFunction Jump_To_Application;
uint32_t jumpAddress;

void goto_booter(void)
{
__disable_irq();
NVIC_SetVectorTable(NVIC_VectTab_FLASH, BOOT_BASE_ADDRESS);
  
jumpAddress = *(__IO uint32_t*) (BOOT_BASE_ADDRESS + 4);
////Jump_To_Application = (pFunction)JumpAddress;
////printk(" Jamp addres=[%x:%x]\r\n",jumpAddress,BOOT_BASE_ADDRESS);	
   Jump_To_Application = (pFunction) jumpAddress;
/* Initialize user application's Stack Pointer */
__set_CONTROL(0) ;
__set_MSP(*(__IO uint32_t*) BOOT_BASE_ADDRESS);
Jump_To_Application();
  
}
void goto_app(void)
{
////uint32_t sp_tst=0;  
__disable_irq();
NVIC_SetVectorTable(NVIC_VectTab_FLASH, APP_BASE_ADDRESS);
jumpAddress = *(__IO uint32_t*) (APP_BASE_ADDRESS + 4);
////sp_tst= *(__IO uint32_t*) (APP_BASE_ADDRESS);
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
////printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
Jump_To_Application = (pFunction)jumpAddress;
/* Initialize user application's Stack Pointer */
__set_CONTROL(0) ;
__set_MSP(*(__IO uint32_t*) APP_BASE_ADDRESS);
Jump_To_Application();
  
}
   
