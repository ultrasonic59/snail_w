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

