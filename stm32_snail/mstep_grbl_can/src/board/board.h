#ifndef __BOARD_H__
#define __BOARD_H__
#include "tx_api.h"

#ifndef APP_NVIC_LOW_IRQ_PRIORITY
#define APP_NVIC_LOW_IRQ_PRIORITY  15U
#endif

////======================================
#ifdef MSTEP_BRD
  #include "mstep_board.h"
#endif
#ifdef STEP_BRD
  #include "step_board.h"
#endif
  #include "my_misc.h"
  #include "stm32f2xx_can.h"

////======================================
////extern void tst_task( void *pvParameters );

#define msleep(ms)  tx_thread_sleep((ULONG)(ms))

#endif
