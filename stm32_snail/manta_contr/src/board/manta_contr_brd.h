#ifndef __MANTA_CONTR_BRD_H__
#define __MANTA_CONTR_BRD_H__
////=============================================
#include "stm32f2xx_conf.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_usart.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"
#include "stm32f2xx_spi.h"
#include "stm32f2xx_i2c.h"
#include "misc.h"
#include "my_types.h"
////=============================================
////============================================
#define DPX_R_TIM_PERIOD 0Xffff
////============= GIRO ========================
////=============SCL2===============================
#define GYRO_SCL_PIN	    GPIO_Pin_10
#define GYRO_SCL_NPIN	  	10
#define GYRO_SCL_PIN_SRC	GPIO_PinSource10
#define GYRO_SCL_GPIO	  	GPIOB
#define GYRO_SCL_RCC_AHB        RCC_AHB1Periph_GPIOB
#define GYRO_SCL_AF             GPIO_AF_I2C2
////=============SDA2===============================
#define GYRO_SDA_PIN	    GPIO_Pin_11
#define GYRO_SDA_NPIN	  	11
#define GYRO_SDA_PIN_SRC	GPIO_PinSource11
#define GYRO_SDA_GPIO	  	GPIOB
#define GYRO_SDA_RCC_AHB        RCC_AHB1Periph_GPIOB
#define GYRO_SDA_AF             GPIO_AF_I2C2
////=============INT===============================
#define GYRO_INT_PIN	    GPIO_Pin_4
#define GYRO_INTA_NPIN	  	4
#define GYRO_INT_GPIO	  	GPIOA
#define GYRO_INT_RCC_AHB        RCC_AHB1Periph_GPIOA
#define GYRO_RCC        RCC_APB1Periph_I2C2
#define GYRO_I2C        I2C2
#define GYRO_ADDR        0x13

////============= MAGN (BMC150)========================
////=============SCL1===============================
#define MAGN_SCL_PIN	    GPIO_Pin_8
#define MAGN_SCL_NPIN	  	8
#define MAGN_SCL_PIN_SRC	GPIO_PinSource8
#define MAGN_SCL_GPIO	  	GPIOB
#define MAGN_SCL_RCC_AHB        RCC_AHB1Periph_GPIOB
#define MAGN_SCL_AF             GPIO_AF_I2C1

////=============SDA1===============================
#define MAGN_SDA_PIN	    GPIO_Pin_9
#define MAGN_SDA_NPIN	  	9
#define MAGN_SDA_PIN_SRC	GPIO_PinSource9
#define MAGN_SDA_GPIO	  	GPIOB
#define MAGN_SDA_RCC_AHB        RCC_AHB1Periph_GPIOB
#define MAGN_SDA_AF             GPIO_AF_I2C1

////=============INT0===============================
#define MAGN_INT0_PIN	    GPIO_Pin_0
#define MAGN_INT0_NPIN	  	0
#define MAGN_INT0_GPIO	  	GPIOC
#define MAGN_INT0_RCC_AHB        RCC_AHB1Periph_GPIOC
////=============INT1===============================
#define MAGN_INT1_PIN	    GPIO_Pin_1
#define MAGN_INT1_NPIN	  	1
#define MAGN_INT1_GPIO	  	GPIOC
#define MAGN_INT1_RCC_AHB        RCC_AHB1Periph_GPIOC

#define MAGN_RCC        RCC_APB1Periph_I2C1
#define MAGN_I2C        I2C1

#define H_MAGN_ADDR        0x15

////============= LED0 ========================
#define LED0_PIN	    GPIO_Pin_9
#define LED0_NPIN	  	9
#define LED0_GPIO	  	GPIOC
#define LED0_RCC_AHB        RCC_AHB1Periph_GPIOC
////============= LED1 ========================
#define LED1_PIN	    GPIO_Pin_8
#define LED1_NPIN	  	8
#define LED1_GPIO	  	GPIOC
#define LED1_RCC_AHB        RCC_AHB1Periph_GPIOC

////============= DP ========================
////============= DPX ========================
////============= DPX_RA ========================
#define DPX_RA_PIN	    	GPIO_Pin_9
#define DPX_RA_PIN_NPIN	    	9
#define DPX_RA_GPIO             GPIOA
#define DPX_RA_RCC  	        RCC_AHB1Periph_GPIOA
#define DPX_RA_AF               GPIO_AF_TIM1
#define DPX_R_TIM               TIM1
#define DPX_R_TIM_RCC           RCC_APB2Periph_TIM1
////============= DPX_RB ========================
#define DPX_RB_PIN	    	GPIO_Pin_8
#define DPX_RB_PIN_NPIN	    	8
#define DPX_RB_GPIO             GPIOA
#define DPX_RB_RCC  	        RCC_AHB1Periph_GPIOA
#define DPX_RB_AF               GPIO_AF_TIM1
////============= DPX_R0 ========================
#define DPX_R0_PIN	    	GPIO_Pin_2
#define DPX_R0_PIN_NPIN	    	2
#define DPX_R0_GPIO             GPIOC
#define DPX_R0_RCC  	        RCC_AHB1Periph_GPIOC
#define DPX_R0_EXTI_PORT        EXTI_PortSourceGPIOC
#define DPX_R0_EXTI_PIN         EXTI_PinSource2
#define DPX_R0_EXTI_LINE        EXTI_Line2
#define DPX_R0_EXTI_IRQn        EXTI2_IRQn 
////============= DPX_LA ========================
#define DPX_LA_PIN	    	GPIO_Pin_1
#define DPX_LA_PIN_NPIN	    	1
#define DPX_LA_GPIO             GPIOA
#define DPX_LA_RCC  	        RCC_AHB1Periph_GPIOA
#define DPX_LA_AF               GPIO_AF_TIM5
#define DPX_L_TIM               TIM5
#define DPX_L_TIM_RCC           RCC_APB1Periph_TIM5
////============= DPX_LB ========================
#define DPX_LB_PIN	    	GPIO_Pin_0
#define DPX_LB_PIN_NPIN	    	0
#define DPX_LB_GPIO             GPIOA
#define DPX_LB_RCC  	        RCC_AHB1Periph_GPIOA
#define DPX_LB_AF               GPIO_AF_TIM5
////==============================================
////==============DPY===========================
////============= DPY_RA ========================
#define DPY_RA_PIN	    	GPIO_Pin_5
#define DPY_RA_PIN_NPIN	    	5
#define DPY_RA_GPIO             GPIOB
#define DPY_RA_RCC  	        RCC_AHB1Periph_GPIOB
#define DPY_RA_AF               GPIO_AF_TIM3
#define DPY_R_TIM               TIM3
#define DPY_R_TIM_RCC           RCC_APB1Periph_TIM3
////============= DPY_RB ========================
#define DPY_RB_PIN	    	GPIO_Pin_4
#define DPY_RB_PIN_NPIN	    	4
#define DPY_RB_GPIO             GPIOB
#define DPY_RB_RCC  	        RCC_AHB1Periph_GPIOB
#define DPY_RB_AF               GPIO_AF_TIM3
////============= DPY_R0 ========================
#define DPY_R0_PIN	    	GPIO_Pin_3
#define DPY_R0_PIN_NPIN	    	3
#define DPY_R0_GPIO             GPIOC
#define DPY_R0_RCC  	        RCC_AHB1Periph_GPIOC
#define DPY_R0_EXTI_PORT        EXTI_PortSourceGPIOC
#define DPY_R0_EXTI_PIN         EXTI_PinSource3
#define DPY_R0_EXTI_LINE        EXTI_Line3
#define DPY_R0_EXTI_IRQn        EXTI3_IRQn 

////============= DPY_LA ========================
#define DPY_LA_PIN	    	GPIO_Pin_7
#define DPY_LA_PIN_NPIN	    	7
#define DPY_LA_GPIO             GPIOB
#define DPY_LA_RCC  	        RCC_AHB1Periph_GPIOB
#define DPY_LA_AF               GPIO_AF_TIM4
#define DPY_L_TIM               TIM4
#define DPY_L_TIM_RCC           RCC_APB1Periph_TIM4
////============= DPY_LB ========================
#define DPY_LB_PIN	    	GPIO_Pin_6
#define DPY_LB_PIN_NPIN	    	6
#define DPY_LB_GPIO             GPIOB
#define DPY_LB_RCC  	        RCC_AHB1Periph_GPIOB
#define DPY_LB_AF               GPIO_AF_TIM4
////==============================================
////=========== DBG_TX ===============================
#define UART_DBG_TX_PIN	    	GPIO_Pin_6
#define UART_DBG_TX_PIN_NPIN	    	6
#define UART_DBG_TX_GPIO        GPIOC
#define UART_DBG_TX_RCC  	RCC_AHB1Periph_GPIOC
////=========== DBG_RX ===============================
#define UART_DBG_RX_PIN	    	GPIO_Pin_7
#define UART_DBG_RX_PIN_NPIN	7
#define UART_DBG_RX_GPIO        GPIOC
#define UART_DBG_RX_RCC  	RCC_AHB1Periph_GPIOC
////=========== BT_TX ===============================
#define UART_BT_TX_PIN	    	GPIO_Pin_2
#define UART_BT_TX_PIN_NPIN	    	2
#define UART_BT_TX_GPIO        GPIOA
#define UART_BT_TX_RCC  	RCC_AHB1Periph_GPIOB
////=========== BT_RX ===============================
#define UART_BT_RX_PIN	    	GPIO_Pin_3
#define UART_BT_RX_PIN_NPIN	3
#define UART_BT_RX_GPIO        GPIOA
#define UART_BT_RX_RCC  	RCC_AHB1Periph_GPIOB
///================= USB ======================
#define USB_DP_PIN	    	GPIO_Pin_12
#define USB_DP_PIN_NPIN	    12
#define USB_DP_PIN_GPIO	    GPIOA
#define USB_DP_PIN_RCC  RCC_APB2Periph_GPIOA

#define USB_DM_PIN	    	GPIO_Pin_11
#define USB_DM_PIN_NPIN	    11
#define USB_DM_PIN_GPIO	    GPIOA
#define USB_DM_PIN_RCC  RCC_APB2Periph_GPIOA
////=================================================================
////#define UART_DBG_TX_GPIO_PORT   GPIOC
////#define UART_DBG_RX_GPIO_PORT   GPIOC
////=================================================================
#define GPIO_CLK_INIT     RCC_AHB1PeriphClockCmd
#define UART_DBG_CLK            RCC_APB2Periph_USART6
#define UART_DBG_CLK_INIT       RCC_APB2PeriphClockCmd

#define UART_DBG_RX_GPIO_CLK    RCC_AHB1Periph_GPIOC
#define UART_DBG_RX_AF          GPIO_AF_USART6
#define UART_DBG_TX_AF          GPIO_AF_USART6
#define UART_DBG                USART6
////=================================================================
#define UART_BT_CLK            RCC_APB1Periph_USART2
#define UART_BT_CLK_INIT       RCC_APB1PeriphClockCmd
#define UART_BT_RX_AF          GPIO_AF_USART2
#define UART_BT_TX_AF          GPIO_AF_USART2
#define UART_BT                USART2
#define UART_BT_IRQn           USART2_IRQn
////==========================================================
#define BT_RX_STACK_SIZE	        ( ( unsigned short ) 1024 )
#define BT_TX_STACK_SIZE	        ( ( unsigned short ) 1024 )
#define APP_PRIORITY	                ( tskIDLE_PRIORITY + 2 )
#define TST_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )
#define TST_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )

////=============================================================
#define I2C_TIMEOUT_MAX 100000

extern dp_dat_t cur_dp_dat;

////======================================

extern void init_gpio(void);
extern void hw_board_init(void);
extern int sendchar6 (int c) ;
extern int get_byte6(void) ;

#define dbg_sendchar  sendchar6 
#define dbg_get_byte get_byte6

extern void clr_all_dp(void);
extern void set_led0(uint8_t i_dat);
extern void set_led1(uint8_t i_dat);
extern void init_i2c(void);
extern uint8_t  get_dpx_r0(void);
extern uint8_t  get_dpy_r0(void);

#define msleep vTaskDelay

////=============================================
#endif ////__MANTA_CONTR_BRD_H__



	
