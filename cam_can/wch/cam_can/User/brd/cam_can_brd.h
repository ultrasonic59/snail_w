#ifndef __CAM_CAN_BRD_H__
#define __CAM_CAN_BRD_H__

#include "debug.h"


////=============led ==================================
  #define LED_PIN          GPIO_Pin_13
  #define LED_GPIO         GPIOB

////=============tst1 ==================================
  #define TST1_PIN          GPIO_Pin_5
  #define TST1_GPIO         GPIOA


extern void gpio_init(void);

extern void set_led(uint8_t idat);
extern void set_tst1(uint8_t on_off);


#endif /* __CAM_CAN_BRD_H__ */


