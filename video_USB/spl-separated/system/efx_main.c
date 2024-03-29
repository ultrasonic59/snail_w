// 本文件由洪旭耀设计，可以通过QQ联系作者：26750452
#include "efxinc.h"

////////////////////////////////////////////////////////////////////////////////
static U64 __StackStartup[1024 / 8] MEM_PI_STACK;
static __task void __ThreadStartup(void);

////////////////////////////////////////////////////////////////////////////////
//|          |
//| 函数名称 |: main
//| 功能描述 |: C语言入口，你懂的！
//|          |:
//| 参数列表 |:
//|          |:
//| 返    回 |:
//|          |:
//| 备注信息 |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
  // 禁用stdout输出缓存
  setbuf(stdout, NULL);
  f1c100s_intc_init();

  // 创建startup线程，所有用户程序都从该线程派生出来
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
//| 函数名称 |: __ThreadStartup
//| 功能描述 |:
//|          |:
//| 参数列表 |:
//|          |:
//| 返    回 |:
//|          |:
//| 备注信息 |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
static void __ThreadStartup(void)
{
  // 作为stdout接口
  DBG_INIT();
  // 建立timer线程，针对RTX系统
  UFX_SetupTaskTimer();
  // 开启开门狗
  target_wdt_setup();

  // 模块加载完成，配置为普通优先级
  os_tsk_prio_self(TSK_PRIO_NORMAL);

  // 执行应用程序代码
  UserEntryInit();
  UserEntryLoop();

  // 如果用户代码返回，就删除该线程
  os_tsk_delete_self();
}


