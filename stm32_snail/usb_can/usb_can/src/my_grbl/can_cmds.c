#include <stdint.h>
#include "my_grbl.h"
////=======================================
int put_can_cmd_reset_all(void)
{
  return 0;
}

void mc_reset(void)
{
put_can_cmd_reset_all();  
report_init_message();
}
