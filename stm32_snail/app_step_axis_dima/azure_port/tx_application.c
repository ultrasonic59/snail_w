#include "tx_api.h"
#include "rtos_compat.h"
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
extern TaskHandle_t can_send_thread_handle;
extern uint16_t VirtAddVarTab[NB_OF_VAR];

void tx_application_define(void *first_unused_memory)
{
    BaseType_t rez;
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

    rez = xTaskCreate(motor_task, "motor_task", MOTOR_TASK_STACK_SIZE, NULL, MOTOR_TASK_PRIORITY, NULL);
    printk("\r\n motor_task[%u]", (unsigned)rez);

    rez = xTaskCreate(can_send_thread, "can_send_thread", CAN_SEND_STACK_SIZE / 2, 0, APP_PRIORITY, &can_send_thread_handle);
    printk("\r\n can_send_thread[%u]", (unsigned)rez);

    rez = xTaskCreate(can_rsv_task, "can_rsv_task", CAN_TASK_STACK_SIZE, NULL, CAN_TASK_PRIORITY, NULL);
    printk("\r\n can_rsv_task[%u]", (unsigned)rez);
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
