#include <stdint.h>
#include "board.h"
#include "my_misc.h"

#include <cmsis_iccarm.h>
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
uint32_t JumpAddress;

void goto_booter(void)
{
JumpAddress = *(__IO uint32_t*) (BOOT_BASE_ADDRESS + 4);
Jump_To_Application = (pFunction)JumpAddress;
/* Initialize user application's Stack Pointer */
__set_MSP(*(__IO uint32_t*) BOOT_BASE_ADDRESS);
Jump_To_Application();
  
}
void goto_app(void)
{
JumpAddress = *(__IO uint32_t*) (APP_BASE_ADDRESS + 4);
Jump_To_Application = (pFunction)JumpAddress;
/* Initialize user application's Stack Pointer */
__set_MSP(*(__IO uint32_t*) APP_BASE_ADDRESS);
Jump_To_Application();
  
}
   
