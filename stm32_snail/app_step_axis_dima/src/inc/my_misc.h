#ifndef __MY_MISC_H__
#define __MY_MISC_H__
#include <stdint.h>

typedef  void (*pFunction)(void);
///=======================================================================
extern void uDelay (const uint32_t usec);
extern void goto_booter(void);
extern void goto_app(void);

#endif ////  __MY_MISC_H__ 
