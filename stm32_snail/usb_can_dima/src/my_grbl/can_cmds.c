#include <stdint.h>
#include "my_grbl.h"
#include "can_cmds.h"
#include "printk.h"
////=======================================
int put_can_cmd_reset_all(void)
{
  return 0;
}

void _mc_reset(void)
{
put_can_cmd_reset_all();  
report_init_message();
}

int put_can_cmd_go(uint8_t dirs,uint16_t per
                   ,uint32_t step_x
                   ,uint32_t step_y
                   ,uint32_t step_z)
{
///go_cmd_t   go_cmd;
#if 1        
        printk("\n\r tst_cnt[%d][%02x][%d][%d][%d]", per, dirs
            , step_x
            , step_y
            , step_z
        );
#endif

  return 0;
}
