#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "cam_can_brd.h"
#include "debug.h"
#include "usb_hid_thr.h"
#include "ch32v30x_usbhs_device.h"
////x#include "usbd_compatibility_hid.h"
extern void USBHS_Send_hid_dat(hid_cmd_t *p_hid_cmd);
extern void set_led_pwm(uint16_t led_pwm);

#if 0
extern void HID_Set_Report_Deal();
void Var_Init(void)
{
    uint16_t i;
    RingBuffer_Comm.LoadPtr = 0;
    RingBuffer_Comm.StopFlag = 0;
    RingBuffer_Comm.DealPtr = 0;
    RingBuffer_Comm.RemainPack = 0;
    for(i=0; i<DEF_Ring_Buffer_Max_Blks; i++)
    {
        RingBuffer_Comm.PackLen[i] = 0;
    }
}
#endif
static uint16_t curr_pwm_val=0;
xQueueHandle ev_rsv_hid;
int parse_hid_cmd(hid_cmd_t *p_hid_cmd)
{
hid_cmd_t t_hid_cmd;
switch(p_hid_cmd->cmd)
    {
    case CMD_SET_LED:
        curr_pwm_val= p_hid_cmd->dat[1]<<8|p_hid_cmd->dat[0];
        set_led_pwm(curr_pwm_val);
        break;
    case CMD_GET_LED:
        t_hid_cmd.cmd=CMD_GET_LED;
        t_hid_cmd.num_bytes=2;
        t_hid_cmd.dat[0]=curr_pwm_val&0xff;
        t_hid_cmd.dat[1]=curr_pwm_val>>8;
        USBHS_Send_hid_dat(&t_hid_cmd);
 ////   curr_pwm_val= p_hid_cmd->dat[1]<<8|p_hid_cmd->dat[0];
 ///   TIM_PWM_set_val(curr_pwm_val);
    break;

}
return 0;
}
void usb_hid_thr(void* pp)
{
printf(" usb_hid_thr\n\r");
////Var_Init();
hid_cmd_t t_hid_cmd;
ev_rsv_hid=xQueueCreate(4,sizeof(hid_cmd_t));
for(;;)
  {
  if (USBHS_DevEnumStatus)
     {
      xQueueReceive(ev_rsv_hid,&t_hid_cmd,portMAX_DELAY);
      parse_hid_cmd(&t_hid_cmd);
      printf(" hid_cmd[%x]\n\r",t_hid_cmd.cmd);

 ///      ;
  ///       UART2_Rx_Service();
   ////      UART2_Tx_Service();
   ////      HID_Set_Report_Deal();
     }

  }

}
