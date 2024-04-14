#ifndef __MISC_H__
#define __MISC_H__

#include <stdint.h>
#include "f1c100s_gpio.h"

#define TEST1_PIN   3
#define TEST1_PORT   GPIOA

extern char sys_uart_getc(void);
extern uint8_t check_key(void);
extern void test_thr(void);
extern void init_test1_pin(void);
extern void put_test1_pin(uint8_t idat);

#endif
