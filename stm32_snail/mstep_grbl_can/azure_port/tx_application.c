#include "tx_api.h"
#include "threadx_app.h"
#include "board.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "printk.h"
#include "eeprom.h"
#include "grbl.h"
#include "can_master.h"

#define GRBL_TASK_STACK_SIZE    1536U
#define VCP_TASK_STACK_SIZE     1024U
#define GRBL_TASK_PRIORITY      4U
#define VCP_TASK_PRIORITY       5U

extern void grbl_task(void *pvParameters);
extern void vcp_thread(void *pdata);
extern TX_THREAD *vcp_thread_handle;

extern USBD_Usr_cb_TypeDef USR_cb;
extern USBD_Class_cb_TypeDef USBD_CDC_VCP_cb;

#pragma data_alignment=8
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

static TX_THREAD grbl_tx_thread;
static TX_THREAD vcp_tx_thread;
static ULONG grbl_stack[GRBL_TASK_STACK_SIZE];
static ULONG vcp_stack[VCP_TASK_STACK_SIZE];

static VOID grbl_thread_entry(ULONG param)
{
  (void)param;
  grbl_task(NULL);
}

static VOID vcp_thread_entry(ULONG param)
{
  (void)param;
  vcp_thread(NULL);
}

void tx_application_define(void *first_unused_memory)
{
  UINT status;

  (void)first_unused_memory;

#ifdef DEBUG
  debug();
#endif
  __disable_irq();
  hw_board_init();

#ifdef USEUSB
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_VCP_cb,
            &USR_cb);
#endif

  printk("\n\r=== usb-grbl-can (ThreadX) ===");
  printk("\n\r=== settings_t [%x]===", (unsigned)sizeof(settings_t));

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  can1_init();
  can_threads_start();

  status = tx_app_thread_create(&vcp_tx_thread, "vcp_thread", vcp_thread_entry, 0U,
                                vcp_stack, sizeof(vcp_stack), VCP_TASK_PRIORITY);
  if (status == TX_SUCCESS) {
    vcp_thread_handle = &vcp_tx_thread;
  }
  printk("\n\r vcp_thread[%u]", (unsigned)status);

  status = tx_app_thread_create(&grbl_tx_thread, "grbl_task", grbl_thread_entry, 0U,
                                grbl_stack, sizeof(grbl_stack), GRBL_TASK_PRIORITY);
  printk("\n\r grbl_task[%u]", (unsigned)status);
  if (status != TX_SUCCESS) {
    printk("\n\r grbl_task create FAILED");
  }

  __enable_irq();
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
