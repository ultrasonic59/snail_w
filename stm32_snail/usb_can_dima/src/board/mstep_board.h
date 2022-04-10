#ifndef __MSTEP_BOARD_H__
#define __MSTEP_BOARD_H__
////=============================================

#include "stm32f2xx_gpio.h"
#include "stm32f2xx_usart.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"
#include "misc.h"

////=============================================
#define	APB1_pres	4
#define APB2_pres	2

#define LED_PWM_TIM_PERIOD     1000
#define LED_PWM_TIM_PRESC     4

#define TST_TIM         TIM8
#define TST_TIM_RCC  	RCC_APB2Periph_TIM8

#define MOT_TIM_PERIOD     6000
#define MOT_TIM_PRESC     8

////#define MOT_STEP_TIM_IRQHandler	 TIM1_TRG_COM_TIM11_IRQHandler
#define MOT_STEP_TIM_IRQHandler	 TIM1_CC_IRQHandler


////#define MOT_STEP_TIM_IRQHandler	TIM8_BRK_TIM12_IRQHandler
////#define TIM8_TRG_COM_TIM14_IRQHandler  MOT_STEP_TIM_IRQHandler	

////#define TIM_LED_FREQ	100000
////#define MOT_TIM_IRQN    TIM1_TRG_COM_TIM11_IRQn////TIM8_BRK_TIM12_IRQn
#define MOT_TIM_IRQN    TIM1_CC_IRQn
#define TIM_LED TST_TIM
////=============== TST1 ============================
#define TST1_PIN	    	GPIO_Pin_9
#define TST1_PIN_NPIN	    	9
#define TST1_PIN_GPIO	    	GPIOA
#define TST1_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=============== TST2============================
#define TST2_PIN	    	GPIO_Pin_7
#define TST2_PIN_NPIN	    	7
#define TST2_PIN_GPIO	    	GPIOA
#define TST2_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=============== TST3 ============================
#define TST3_PIN	    	GPIO_Pin_8
#define TST3_PIN_NPIN	    	8
#define TST3_PIN_GPIO	    	GPIOA
#define TST3_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=============== TST4 ============================
#define TST4_PIN	    	GPIO_Pin_6
#define TST4_PIN_NPIN	    	6
#define TST4_PIN_GPIO	    	GPIOA
#define TST4_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=============== TST5 ============================
#define TST5_PIN	    	GPIO_Pin_9
#define TST5_PIN_NPIN	    	9
#define TST5_PIN_GPIO	    	GPIOC
#define TST5_PIN_RCC  	        RCC_AHB1Periph_GPIOC
////=============== TST6 ============================
#define TST6_PIN	    	GPIO_Pin_5
#define TST6_PIN_NPIN	    	5
#define TST6_PIN_GPIO	    	GPIOA
#define TST6_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=============== TST7 ============================
#define TST7_PIN	    	GPIO_Pin_8
#define TST7_PIN_NPIN	    	8
#define TST7_PIN_GPIO	    	GPIOC
#define TST7_PIN_RCC  	        RCC_AHB1Periph_GPIOC
#define TST7_TIM_RCC  	        RCC_APB2Periph_TIM8

#define TST7_TIM  	        TIM8

////=============== TST8 ============================
#define TST8_PIN	    	GPIO_Pin_4
#define TST8_PIN_NPIN	    	4
#define TST8_PIN_GPIO	    	GPIOA
#define TST8_PIN_RCC  	        RCC_AHB1Periph_GPIOA
////=========== DBG_TX ===============================
#define UART_DBG_TX_PIN	    	GPIO_Pin_2
#define UART_DBG_TX_PIN_NPIN	    	2
#define UART_DBG_TX_GPIO        GPIOA
#define UART_DBG_TX_RCC  	RCC_AHB1Periph_GPIOA
////=========== DBG_RX ===============================
#define UART_DBG_RX_PIN	    	GPIO_Pin_3
#define UART_DBG_RX_PIN_NPIN	3
#define UART_DBG_RX_GPIO        GPIOA
#define UART_DBG_RX_RCC  	RCC_AHB1Periph_GPIOA
////=============== MOT_FAULT ============================
#define MOT_FAULT_PIN	    		GPIO_Pin_0
#define MOT_FAULT_PIN_NPIN	    	0
#define MOT_FAULT_PIN_GPIO	    	GPIOB
#define MOT_FAULT_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_M2 ============================
#define MOT_M2_PIN	    	GPIO_Pin_1
#define MOT_M2_PIN_NPIN	        1
#define MOT_M2_PIN_GPIO	        GPIOB
#define MOT_M2_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_M1 ============================
#define MOT_M1_PIN	    	GPIO_Pin_2
#define MOT_M1_PIN_NPIN	        2
#define MOT_M1_PIN_GPIO	        GPIOB
#define MOT_M1_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_M0 ============================
#define MOT_M0_PIN	    	GPIO_Pin_10
#define MOT_M0_PIN_NPIN	        10
#define MOT_M0_PIN_GPIO	        GPIOB
#define MOT_M0_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_ENA ============================
#define MOT_ENA_PIN	    	GPIO_Pin_11
#define MOT_ENA_PIN_NPIN	11
#define MOT_ENA_PIN_GPIO	GPIOB
#define MOT_ENA_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_RESET ============================
#define MOT_RESET_PIN	    	GPIO_Pin_12
#define MOT_RESET_PIN_NPIN	12
#define MOT_RESET_PIN_GPIO	GPIOB
#define MOT_RESET_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_SLEEP ============================
#define MOT_SLEEP_PIN	    	GPIO_Pin_13
#define MOT_SLEEP_PIN_NPIN	13
#define MOT_SLEEP_PIN_GPIO	GPIOB
#define MOT_SLEEP_PIN_RCC  	RCC_AHB1Periph_GPIOB
////=============== MOT_STEP ============================
#define MOT_STEP_PIN	    	GPIO_Pin_14
#define MOT_STEP_PIN_NPIN	14
#define MOT_STEP_PIN_GPIO	GPIOB
#define MOT_STEP_PIN_RCC  	RCC_AHB1Periph_GPIOB
#define MOT_STEP_TIM  	        TIM1
#define MOT_STEP_TIM_RCC  	RCC_APB2Periph_TIM1

////=============== MOT_DIR ============================
#define MOT_DIR_PIN	    	GPIO_Pin_6
#define MOT_DIR_PIN_NPIN	    6
#define MOT_DIR_PIN_GPIO	    GPIOC
#define MOT_DIR_PIN_RCC  	RCC_AHB1Periph_GPIOC
////============== LED_PWM TIM12ch2 TIM8_CH3N ============================
#define LED_PWM_PIN	    	GPIO_Pin_15
#define LED_PWM_PIN_NPIN	15
#define LED_PWM_PIN_GPIO	GPIOB
#define LED_PWM_PIN_RCC  	RCC_AHB1Periph_GPIOB
#define LED_PWM_TIM_RCC  	RCC_APB2Periph_TIM8
#define LED_PWM_TIM  	        TIM8

////=============== CONC ============================
#define CONC_PIN	    GPIO_Pin_7
#define CONC_PIN_NPIN	    7
#define CONC_PIN_GPIO	    GPIOC
#define CONC_PIN_RCC  	    RCC_AHB1Periph_GPIOC
////=============== UART_RX1 ============================
#define UART_RX1_PIN	    	    GPIO_Pin_7
#define UART_RX1_PIN_NPIN	    7
#define UART_RX1_PIN_GPIO	    GPIOB
#define UART_RX1_PIN_RCC  	    RCC_AHB1Periph_GPIOB
////=============== UART_TX1 ============================
#define UART_TX1_PIN	    	    GPIO_Pin_6
#define UART_TX1_PIN_NPIN	    6
#define UART_TX1_PIN_GPIO	    GPIOB
#define UART_TX1_PIN_RCC  	    RCC_AHB1Periph_GPIOB
#define UART1_CLK                   RCC_APB2Periph_USART1
#define UART_CLK_INIT               RCC_APB2PeriphClockCmd

#define UART1_RX_AF                 GPIO_AF_USART1
#define UART1_TX_AF                 GPIO_AF_USART1

////============== CAN1_RX ============================
#define CAN1_RX_PIN	    	GPIO_Pin_8
#define CAN1_RX_PIN_SOURCE	GPIO_PinSource8
#define CAN1_RX_SOURCE              GPIO_PinSource8
#define CAN1_RX_PIN_NPIN	8
#define CAN1_RX_PIN_GPIO	GPIOB
#define CAN1_RX_PIN_RCC  	RCC_AHB1Periph_GPIOB
////============== CAN1_TX ============================
#define CAN1_TX_PIN	    	GPIO_Pin_9
#define CAN1_TX_PIN_SOURCE	GPIO_PinSource9
#define CAN1_TX_SOURCE              GPIO_PinSource9
#define CAN1_TX_PIN_NPIN	9
#define CAN1_TX_PIN_GPIO	GPIOB
#define CAN1_TX_PIN_RCC  	RCC_AHB1Periph_GPIOB
////============== CAN1_INH ============================
#define CAN1_INH_PIN	    	GPIO_Pin_0
#define CAN1_INH_PIN_NPIN	    0
#define CAN1_INH_PIN_GPIO	    GPIOC
#define CAN1_INH_PIN_RCC  	RCC_AHB1Periph_GPIOC
////============== ON_LED0 ============================
#define ON_LED0_PIN	    	GPIO_Pin_0
#define ON_LED0_PIN_NPIN	0
#define ON_LED0_PIN_GPIO	GPIOA
#define ON_LED0_PIN_RCC  	RCC_AHB1Periph_GPIOA
////============== ON_LED1 ============================
#define ON_LED1_PIN	    	GPIO_Pin_1
#define ON_LED1_PIN_NPIN	1
#define ON_LED1_PIN_GPIO	GPIOA
#define ON_LED1_PIN_RCC  	RCC_AHB1Periph_GPIOA
////================= USB ======================
#define USB_DP_PIN	    	GPIO_Pin_12
#define USB_DP_PIN_NPIN	    12
#define USB_DP_PIN_GPIO	    GPIOA
#define USB_DP_PIN_RCC  RCC_APB2Periph_GPIOA

#define USB_DM_PIN	    	GPIO_Pin_11
#define USB_DM_PIN_NPIN	    11
#define USB_DM_PIN_GPIO	    GPIOA
#define USB_DM_PIN_RCC  RCC_APB2Periph_GPIOA
////=================================================================
#define UART_DBG_TX_GPIO_PORT   GPIOA
#define UART_DBG_RX_GPIO_PORT   GPIOA
////=================================================================
////=======================================================
#define CAN1_CLK                    RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 GPIO_Pin_8
#define CAN1_TX_PIN                 GPIO_Pin_9
#define CAN1_GPIO_PORT              GPIOB
#define CAN1_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN1_AF_PORT                GPIO_AF_CAN1
#define CAN1_RX_SOURCE              GPIO_PinSource8
#define CAN1_TX_SOURCE              GPIO_PinSource9

////=================================================================
#define GPIO_CLK_INIT     RCC_AHB1PeriphClockCmd
#define UART_DBG_CLK            RCC_APB1Periph_USART2
#define UART_DBG_CLK_INIT       RCC_APB1PeriphClockCmd

#define UART_DBG_RX_GPIO_CLK    RCC_AHB1Periph_GPIOA
#define UART_DBG_RX_AF          GPIO_AF_USART2
#define UART_DBG_TX_AF          GPIO_AF_USART2
#define UART_DBG                USART2
#define UART_DBG_TX_SOURCE      GPIO_Pin_2
#define UART_DBG_RX_SOURCE      GPIO_Pin_3
////=================================================================

extern void init_gpio(void);
extern void hw_board_init(void);
extern void  on_led0(uint8_t idat);
extern void  on_led1(uint8_t idat);
extern void set_led_dutycycle (uint32_t val);
extern void put_mot_nstep(uint32_t nstep);
extern void  set_sleep_mot(uint8_t idat);
extern void  set_ena_mot(uint8_t idat);
extern void  set_dir_mot(uint8_t idat);
extern void  set_reset_mot(uint8_t idat);
extern void set_mot_rej(uint8_t rej);
extern int sendchar2 (int c) ;
extern int get_byte2(void) ;

#define dbg_sendchar  sendchar2 
#define dbg_get_byte get_byte2
////=============================================
extern void uDelay (const uint32_t usec);
////=============================================

#endif ////__BOARD_H__



	
