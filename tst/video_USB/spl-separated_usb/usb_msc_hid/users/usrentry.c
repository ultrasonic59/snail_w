// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#include <efxinc.h>
#include <f1c100s-irq.h>
#include <tusb.h>
#include <ctype.h>

__task void usb_task() {
  for (;;) {
		tud_task();
	}
}


////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: UserEntryInit
//| �������� |: Ӧ�ó����ʼ��
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
void UserEntryInit(void)
{
  target_wdt_feed();

  printf("DDR size: %uMB\n", (*(uint32_t*)0x5c) & 0xFFFFFF);
	tusb_init();
	os_tsk_create(usb_task, 10);
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: UserEntryLoop
//| �������� |: Ӧ�ó�����ѭ��
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
void UserEntryLoop(void)
{
  for (;;) {
    target_wdt_feed();
		sys_delay(500);
#if 0
    // ������������
    if (f1c100s_uart_isTxEnd(UART0_MID)) {
      rCnt = f1c100s_uart_readFifo(UART0_MID, rbuffer, sizeof(rbuffer));
      if (rCnt > 0) {
        f1c100s_uart_asyncTx(UART0_MID, rbuffer, rCnt);
      }
    }
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
	printf("tud_mount_cb\r\n");
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
	printf("tud_umount_cb\r\n");
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
	printf("tud_suspend_cb\r\n");
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
	printf("tud_resume_cb\r\n");
}

#if CFG_TUD_HID
//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;
	printf("tud_hid_get_report_cb\r\n");

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // This example doesn't use multiple report and report ID
  (void) itf;
  (void) report_id;
  (void) report_type;

  // echo back anything we received from host
  tud_hid_report(0, buffer, bufsize);
	printf("tud_hid_set_report_cb bufsize: %d, buffer: %s\r\n", bufsize, buffer);
}
#endif
