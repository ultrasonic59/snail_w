// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#include "efxinc.h"

////////////////////////////////////////////////////////////////////////////////
static U64 __StackStartup[1024 / 8] MEM_PI_STACK;
static __task void __ThreadStartup(void);

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: main
//| �������� |: C������ڣ��㶮�ģ�
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
  // ����stdout�������
  setbuf(stdout, NULL);
  f1c100s_intc_init();

  // ����startup�̣߳������û����򶼴Ӹ��߳���������
  util_enable_interrupt();
  os_sys_init_user(__ThreadStartup,
                   TSK_PRIO_HIGHEST,
                   __StackStartup,
                   sizeof(__StackStartup));
  util_halt();
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: __ThreadStartup
//| �������� |:
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
static void __ThreadStartup(void)
{
  // ��Ϊstdout�ӿ�
  DBG_INIT();
  // ����timer�̣߳����RTXϵͳ
  UFX_SetupTaskTimer();
  // �������Ź�
  target_wdt_setup();

  // ģ�������ɣ�����Ϊ��ͨ���ȼ�
  os_tsk_prio_self(TSK_PRIO_NORMAL);

  // ִ��Ӧ�ó������
  UserEntryInit();
  UserEntryLoop();

  // ����û����뷵�أ���ɾ�����߳�
  os_tsk_delete_self();
}


