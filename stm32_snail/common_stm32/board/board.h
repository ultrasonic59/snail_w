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
#ifdef DIMA_BRD
  #include "dima_board.h"
  #include "my_misc.h"
#endif
#ifdef DIMA_BRD_V2
  #include "dima_board_v2.h"
  #include "my_misc.h"
#endif

  #include "stm32f2xx_can.h"
///========================================
#define CTRL_MODE_MASK (0xf<<3)
#define CTRL_MODE_OFFS 3
#define CTRL_TORQUE_MASK (0xff)
#define CTRL_TORQUE_OFFS 0

////======================================
////extern void tst_task( void *pvParameters );
extern int32_t curr_coord;
extern uint8_t use_enc;
extern int32_t next_coord;

#define msleep(ms)  tx_thread_sleep((ULONG)(ms))
#ifndef _MASTER_
////extern int32_t cur_coord;
extern uint8_t cur_state;
#endif
extern uint8_t get_conc_n(void);
extern uint8_t ena_check_conc;
#endif
