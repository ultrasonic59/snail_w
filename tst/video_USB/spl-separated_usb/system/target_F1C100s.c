// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#include "target.h"

////////////////////////////////////////////////////////////////////////////////
// �ṩ��λ����MCU�Ĺ��ܣ�����CPU�ں˼���Χ�豸��ͨ������WDT��
////////////////////////////////////////////////////////////////////////////////
static volatile bool_t bReset = 0;

void target_reset(void)
{
  CPU_SR_DECL;

  bReset = true;
  CPU_ENTER_CRITICAL();
  CPU_EXIT_CRITICAL();
  util_halt();
}

void target_wdt_setup(void)
{
  CPU_SR_DECL;

  CPU_ENTER_CRITICAL();
  CPU_EXIT_CRITICAL();
}

void target_wdt_feed(void)
{
  CPU_SR_DECL;

  if (!bReset) {
    CPU_ENTER_CRITICAL();
    CPU_EXIT_CRITICAL();
  }
}

