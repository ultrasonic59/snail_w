/*
 * enc6701_brd.h
 *
 *  Created on: Dec 21, 2023
 *      Author: vagol
 */

#ifndef _ENC6701_BRD_H_
#define _ENC6701_BRD_H_
#include "ch32v00x_conf.h"
#define BR_ENC  230400    ///;///460800;///115200;
///========================================
////=============dbg_rx==================================
  #define SOFT_RX_PIN          GPIO_Pin_0
  #define SOFT_RX_GPIO         GPIOC
 #define SOFT_RX_TIM           TIM1
////============= dbg_tx ==================================
  #define SOFT_TX_PIN          GPIO_Pin_6
  #define SOFT_TX_GPIO         GPIOC
 #define SOFT_TX_TIM           TIM2
////=============led==================================
  #define LED_PIN          GPIO_Pin_7
  #define LED_GPIO         GPIOC
////=============i2c==================================
  #define SDA_PIN          GPIO_Pin_1
  #define SDA_GPIO         GPIOC
  #define SCL_PIN          GPIO_Pin_2
  #define SCL_GPIO         GPIOC
////=============RT==================================
  #define RT_PIN          GPIO_Pin_4
  #define RT_GPIO         GPIOC
////=============uart_rx==================================
  #define URX_PIN          GPIO_Pin_6
  #define URX_GPIO         GPIOD
////============= uart_tx ==================================
  #define UTX_PIN          GPIO_Pin_5
  #define UTX_GPIO         GPIOD
///========================================

#define TIMER_PER 1000
#define TIMER_PRE 100

#define HOST_MODE   0
#define SLAVE_MODE   1

/* I2C Communication Mode Selection */
#define I2C_MODE   HOST_MODE
///#define I2C_MODE   SLAVE_MODE
typedef struct send_data_s{
uint16_t coord;
uint16_t val;
}send_data_t;

///#define RXAdderss   0x02

extern void init_gpio(void);
extern void set_led(uint8_t on_off);
extern void init_hw(void);

#endif /* ENC6701_BRD_H_ */
