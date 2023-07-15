// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#ifndef __EFX_INC_H__
#define __EFX_INC_H__

#include "ftypes.h"
#include "fdebug.h"
#include "target.h"
#include <stdlib.h>
#include <string.h>
#ifdef __RTX
#include "RTL.h"
#endif

#ifdef __cplusplus
extern "C"  {
#endif

#define TWAIT_FOREVER       (0xFFFF)  // ����ʱ

#define TSK_PRIO_RESERVED   (255) // �������ȼ�
#define TSK_PRIO_HILIMIT    (254) // ���ȼ�����
#define TSK_PRIO_HIGHEST    (50)  // ������ȼ�
#define TSK_PRIO_HIGHER     (40)  // ƫ�����ȼ�
#define TSK_PRIO_NORMAL     (30)  // ��ͨ���ȼ�
#define TSK_PRIO_LOWER      (20)  // ƫ�����ȼ�
#define TSK_PRIO_LOWEST     (10)  // ������ȼ�
#define TSK_PRIO_LOLIMIT    (1)   // ���ȼ�����
#define TSK_PRIO_IDLE       (0)   // �������ȼ�

extern volatile U32 os_time;      // ��rt_Time.oģ�鵼��
#define sys_tick os_time          // ������CPU���ݿ��

static inline void timer_start(U32* pTimer)
{
  *pTimer = sys_tick;
}

static inline int timer_expired(U32* pTimer, U32 dly)
{
  U32 elapsed = sys_tick - *pTimer;
  return (elapsed >= dly);
}

#define sys_delay(ms) os_dly_wait(ms)

// ��ǰ�߳������ó�CPU����һ��(ͬ���ȼ�)�߳�
#define sys_yield() os_dly_wait(1)

// ����ǰ�����̣߳�������OSTaskResume()����ʹ֮������
static inline void sys_suspend(void)
{
  os_dly_wait(TWAIT_FOREVER);
}

/* ������<RTX_Conf_xxx.c>�ļ��� */
void   UFX_SetupTaskTimer(void);
bool_t UFX_AddTaskTimer(U16 dly, void (*pfn)(void*), void* parg);
/* ������<drv-loader.c>�ļ��� */
bool_t UFX_LoadDrivers(void);
/* �û������ʼ�� */
void   UserEntryInit(void);
/* �û�����ѭ�� */
void   UserEntryLoop(void);



#ifdef __cplusplus
}
#endif

#endif /* __EFX_INC_H__ */



