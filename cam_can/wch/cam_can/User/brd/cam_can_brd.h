#ifndef __CAM_CAN_BRD_H__
#define __CAM_CAN_BRD_H__

#include "debug.h"

#define DOZA_BRD    1

#define DEF_PER    1000
#define DEF_PRESC  50-1   //48000-1
#define INIT_VAL  0

/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2   1

/* PWM Output Mode Selection */
#define PWM_MODE PWM_MODE1
//#define PWM_MODE PWM_MODE2

////============= PWM_LED ==================================
  #define PWM_LED_PIN          GPIO_Pin_6
  #define PWM_LED_GPIO         GPIOC
  #define TIM_PWM              TIM8
////============= ON_DV ==================================
  #define ON_DV_PIN          GPIO_Pin_8
  #define ON_DV_GPIO         GPIOC
////============= CAN ==================================
  #define CANx                CAN2

  #define CAN_RX_PIN          GPIO_Pin_12
  #define CAN_RX_GPIO         GPIOB
  #define CAN_TX_PIN          GPIO_Pin_13
  #define CAN_TX_GPIO         GPIOB
////============= INH ==================================
  #define INH_PIN          GPIO_Pin_7
  #define INH_GPIO         GPIOC
////=============led ==================================
  #define LED_PIN          GPIO_Pin_14
  #define LED_GPIO         GPIOB
////=============tst1 ==================================
  #define TST1_PIN          GPIO_Pin_5
  #define TST1_GPIO         GPIOA
////=============tst2 ==================================
  #define TST2_PIN          GPIO_Pin_10
  #define TST2_GPIO         GPIOB
////=============tst3 ==================================
  #define TST3_PIN          GPIO_Pin_11
  #define TST3_GPIO         GPIOB
///===================================================
////#define MOTOR_TASK_STACK_SIZE           1024            ////( configMINIMAL_STACK_SIZE + 50 )
////#define MOTOR_TASK_PRIORITY             ( tskIDLE_PRIORITY + 3 )
#define CAN_SEND_STACK_SIZE                 512////1024////
#define CAN_TASK_STACK_SIZE                 512///1024            ////
#define CAN_TASK_PRIORITY               ( tskIDLE_PRIORITY + 8 )
#define USB_HID_STACK_SIZE                 512  ////1024            ////
#define USB_HID_TASK_PRIORITY               ( tskIDLE_PRIORITY + 8 )

#define APP_PRIORITY                           (6)

////#define TST_TASK_STACK_SIZE         1024            ////( configMINIMAL_STACK_SIZE + 50 )
////#define TST_TASK_PRIORITY               ( tskIDLE_PRIORITY + 3 )

///===================================================
extern void gpio_init(void);

extern void on_off_dv(uint8_t on_off);
extern void set_led(uint8_t idat);
extern void set_inh(uint8_t idat);
extern void set_tst1(uint8_t on_off);
extern void set_tst2(uint8_t on_off);
extern void set_tst3(uint8_t on_off);
extern void board_init(void);

#define msleep vTaskDelay


#endif /* __CAM_CAN_BRD_H__ */


