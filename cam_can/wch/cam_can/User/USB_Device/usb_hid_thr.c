#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "cam_can_brd.h"
#include "debug.h"
#include "usb_hid_thr.h"
#include "ch32v30x_usbhs_device.h"

extern void HID_Set_Report_Deal();

void usb_hid_thr(void* pp)
{
printf(" usb_hid_thr\n\r");
for(;;)
  {
  if (USBHS_DevEnumStatus)
     {
        ;
////         UART2_Rx_Service();
////         UART2_Tx_Service();
         HID_Set_Report_Deal();
     }

  }

}
