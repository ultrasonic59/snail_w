#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "cam_can_brd.h"
#include "debug.h"
#include "usb_hid_thr.h"
#include "ch32v30x_usbhs_device.h"
////#include "usbd_compatibility_hid.h"
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
void usb_hid_thr(void* pp)
{
printf(" usb_hid_thr\n\r");
////Var_Init();

for(;;)
  {
  if (USBHS_DevEnumStatus)
     {
       ;
  ///       UART2_Rx_Service();
   ////      UART2_Tx_Service();
   ////      HID_Set_Report_Deal();
     }

  }

}
