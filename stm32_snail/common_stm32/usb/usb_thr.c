#include "tx_api.h"
#include "threadx_app.h"
#include "my_types.h"
#include "printk.h"
#include "usb_dcd_int.h"

extern uint32_t USBD_OTG_ISR_Handler(USB_OTG_CORE_HANDLE *pdev);

#ifdef USE_USB_THR
tx_app_queue_t *q_usb_in;

void usb_thread(void *arg)
{
  usb_req_t t_usb_req;

  (void)arg;
  if (tx_app_queue_create(&q_usb_in, sizeof(usb_req_t), 80U) != TX_SUCCESS) {
    return;
  }
  for (;;) {
    if (tx_app_queue_receive(q_usb_in, &t_usb_req, TX_APP_WAIT_FOREVER) == TX_SUCCESS) {
      if (t_usb_req.in_out == 0) {
        USBD_DCD_INT_fops->DataOutStage((void *)t_usb_req.addr_dev, t_usb_req.num_point);
      } else {
        USBD_DCD_INT_fops->DataInStage((void *)t_usb_req.addr_dev, t_usb_req.num_point);
      }
    }
  }
}
#endif

void my_USBD_OTG_ISR_Handler(USB_OTG_CORE_HANDLE *pdev)
{
  USBD_OTG_ISR_Handler(pdev);
}

void USB_OTG_EnableSuspend(USB_OTG_CORE_HANDLE *pdev)
{
  USB_OTG_GINTMSK_TypeDef int_mask;

  int_mask.d32 = 0;
  int_mask.b.usbsuspend = 1;
  USB_OTG_MODIFY_REG32(&pdev->regs.GREGS->GINTMSK, int_mask.d32, NULL);
}

void USB_OTG_DisableSuspend(USB_OTG_CORE_HANDLE *pdev)
{
  USB_OTG_GINTMSK_TypeDef int_mask;

  int_mask.d32 = 0;
  int_mask.b.usbsuspend = 1;
  USB_OTG_MODIFY_REG32(&pdev->regs.GREGS->GINTMSK, NULL, int_mask.d32);
}
