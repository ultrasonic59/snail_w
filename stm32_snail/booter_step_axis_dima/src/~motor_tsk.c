#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "board.h"
#include "board.h"
#include "printk.h"

#include "snail_can_cmds.h"

cmd_t cur_cmd={0};

void motor_task( void *pvParameters )
{
///uint8_t btst=0; 
uint8_t psk=0; 
///uint16_t tst;
char key=0;
int nstep=300;
uint8_t dir=0;
uint8_t mot_rej=0;
printk("\n\r motor_task"); 
motor_init();

#if 0
set_sleep_mot(1);
////set_ena_mot(1);
set_reset_mot(1);
uDelay(1000);
set_reset_mot(0);
uDelay(20000);
init_step_mot();
////set_ena_mot(0);
///tst=mot_spi_rd(0x0);
///tst|=0x1;
///mot_spi_wr(0x0,tst);
 ena_mot(0) ;
#endif
 
for(;;)
{
if(check_push_key_dbg())
  {
  key=get_byte_dbg() ;  
  switch(key)
    {
    case 'a':
      nstep += 20;
      break;
    case 's':
      if(nstep)
        nstep-= 20;
        break;
    case 'd':
      dir ++;
      dir&=0x1;
      break;
    case 'm':
      mot_rej ++;
      if(mot_rej>8)
        mot_rej=0;
 ////     mot_rej&=0x7;
      break;
    case 'p':
     psk=1;
      break;
    case 'z':
     print_mot_reg();
      break;
    
   }
  printk("\n\r nstep[%d] dir[%x] Mot_rej[%x]",nstep,dir,mot_rej); 
  set_dir_mot(dir);
  set_mot_rej(mot_rej);
  if(psk)
    {
    put_mot_nstep(nstep);
    psk=0;
    }
  
  }  
}
}

