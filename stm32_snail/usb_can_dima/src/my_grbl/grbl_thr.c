#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "printk.h"

TaskHandle_t  grbl_thread_handle;

void grbl_thread(void* pp)
{
printk("\n\r grbl_thread\n\r"); 
 
for (;;) 
  {
  ; 
  }  
}