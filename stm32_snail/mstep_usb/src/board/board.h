#ifndef __BOARD_H__
#define __BOARD_H__
////======================================
#define CFG_TUSB_MCU OPT_MCU_STM32F2
////#define USB_OTG_FS_MAX_IN_ENDPOINTS     3
///#define USB_OTG_FS_TOTAL_FIFO_SIZE      1250
////======================================
#ifdef MSTEP_BRD
  #include "mstep_board.h"
#endif
#ifdef STEP_BRD
  #include "step_board.h"
#endif
#define VCP_RX_STACK_SIZE	        1024////( ( unsigned short ) 512 )
#define VCP_TX_STACK_SIZE	      1024//// ( ( unsigned short ) 512 )
#define         APP_PRIORITY	      (6)	
#define APPLICATION_STACK_SIZE         (4000)

////======================================
extern void tst_task( void *pvParameters );

#endif