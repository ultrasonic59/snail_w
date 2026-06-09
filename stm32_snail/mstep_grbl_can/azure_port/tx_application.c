#include "tx_api.h"
#include "rtos_compat.h"
#include "board.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "printk.h"
#include "eeprom.h"
#include "grbl.h"
#include "can_master.h"

#define GRBL_TASK_STACK_SIZE    1536
#define VCP_TASK_STACK_SIZE     1024
#define GRBL_TASK_PRIORITY      (tskIDLE_PRIORITY + 4)
#define VCP_TASK_PRIORITY       (tskIDLE_PRIORITY + 5)

extern void grbl_task(void *pvParameters);
extern void vcp_thread(void *pdata);
extern TaskHandle_t vcp_thread_handle;

extern USBD_Usr_cb_TypeDef USR_cb;
extern USBD_Class_cb_TypeDef USBD_CDC_VCP_cb;

#pragma data_alignment=8
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

void tx_application_define(void *first_unused_memory)
{
    BaseType_t rez;
    (void)first_unused_memory;

#ifdef DEBUG
    debug();
#endif
    /* Same order as src/main.c (FreeRTOS): UART before USB, printk with IRQ off. */
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

    can1_init();
    can_threads_start();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* vcp first: higher priority (+5), pumps USB CDC into grbl serial buffers */
    rez = xTaskCreate(vcp_thread, "vcp_thread", VCP_TASK_STACK_SIZE, 0, VCP_TASK_PRIORITY, &vcp_thread_handle);
    printk("\n\r vcp_thread[%u]", (unsigned)rez);

    rez = xTaskCreate(grbl_task, "grbl_task", GRBL_TASK_STACK_SIZE, NULL, GRBL_TASK_PRIORITY, NULL);
    printk("\n\r grbl_task[%u]", (unsigned)rez);
    if (rez == 0U) {
        printk("\n\r grbl_task create FAILED (rtos pool?)");
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
