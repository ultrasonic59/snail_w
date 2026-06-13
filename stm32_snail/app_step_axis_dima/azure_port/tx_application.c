#include "tx_api.h"
#include "threadx_app.h"
#include "board.h"
#include "misc.h"
#include "printk.h"
#include "emul_eeprom.h"
#include "hdlc.h"

#define VERS "snail_axis_v1.2.3"

extern void can_rsv_task(void *pvParameters);
extern void can_send_thread(void *pp);

extern uint8_t boot_state;
extern uint16_t cur_conf;
extern TX_THREAD *can_send_thread_handle;
extern uint16_t VirtAddVarTab[NB_OF_VAR];

static TX_THREAD motor_tx_thread;
static TX_THREAD can_send_tx_thread;
static TX_THREAD can_rsv_tx_thread;
static ULONG motor_stack[MOTOR_TASK_STACK_SIZE];
static ULONG can_send_stack[CAN_SEND_STACK_SIZE / 2U];
static ULONG can_rsv_stack[CAN_TASK_STACK_SIZE];

static VOID motor_thread_entry(ULONG param)
{
  (void)param;
  motor_task(NULL);
}

static VOID can_send_thread_entry(ULONG param)
{
  (void)param;
  can_send_thread(NULL);
}

static VOID can_rsv_thread_entry(ULONG param)
{
  (void)param;
  can_rsv_task(NULL);
}

void tx_application_define(void *first_unused_memory)
{
  UINT status;
  uint16_t tmp = 0;

  (void)first_unused_memory;

#ifdef DEBUG
  debug();
#endif

  __disable_irq();
  hw_board_init();
  boot_state = BOOTER_NO_BOOT;

#if STEP_X
  printk("\r\n[app_step_x_axis][%s]%s:%s] (ThreadX)", VERS, __DATE__, __TIME__);
#elif STEP_Y
  printk("\r\n[app_step_y_axis][%s]%s:%s] (ThreadX)", VERS, __DATE__, __TIME__);
#elif STEP_Z
  printk("\r\n[app_step_z_axis][%s]%s:%s] (ThreadX)", VERS, __DATE__, __TIME__);
#else
  #error "STEP_X / STEP_Y / STEP_Z must be defined"
#endif

  FLASH_Unlock();
  EE_Init();
  FLASH_Lock();

  if (EE_Rd(ADDR_EEPROM_CONF, &tmp) == 0) {
    cur_conf = tmp;
  }

  hdlc_init(&g_hdlc);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  can_send_thread_handle = &can_send_tx_thread;

  status = tx_app_thread_create(&motor_tx_thread, "motor_task", motor_thread_entry, 0U,
                                motor_stack, sizeof(motor_stack), MOTOR_TASK_PRIORITY);
  printk("\r\n motor_task[%u]", (unsigned)status);

  status = tx_app_thread_create(&can_send_tx_thread, "can_send_thread", can_send_thread_entry, 0U,
                                can_send_stack, sizeof(can_send_stack), APP_PRIORITY);
  printk("\r\n can_send_thread[%u]", (unsigned)status);

  status = tx_app_thread_create(&can_rsv_tx_thread, "can_rsv_task", can_rsv_thread_entry, 0U,
                                can_rsv_stack, sizeof(can_rsv_stack), CAN_TASK_PRIORITY);
  printk("\r\n can_rsv_task[%u]", (unsigned)status);
}

int main(void)
{
  tx_kernel_enter();
  return 0;
}

#ifdef DEBUG
void assert_failed(unsigned char *pcFile, unsigned long ulLine)
{
  (void)pcFile;
  (void)ulLine;
  for (;;)
    ;
}
#endif
