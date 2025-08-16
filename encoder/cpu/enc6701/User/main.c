/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *
 */

#include <string.h>
#include <stdlib.h>
#include "debug.h"

#include "../brd/enc6701_brd.h"
#include "timers.h"

#include "softuart.h"
#include "adc.h"
#include "i2c.h"

////https://www.youtube.com/watch?v=PtW0C0qOq-o

/* Global define */
/* I2C Mode Definition */
#define HOST_MODE   0
#define SLAVE_MODE   1

/* I2C Communication Mode Selection */
#define I2C_MODE   HOST_MODE
///#define I2C_MODE   SLAVE_MODE

#define RXAdderss   0x02

/* Global Variable */
vu8 cur_val=0;

///===================================================
///====================================================================

///===================================================
uint8_t tmp[20] = {0x01, 0x80, 0xaa, 0x55};

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
#define LEN_BUF 32
int main(void)
{
    int t_rez=0;
uint8_t tst =0;
uint16_t rdat;
static uint16_t prev_enc=0;
///static uint16_t prev_adc=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    ///========================================
    init_hw();
///    init_gpio();

 ///  TIM1_Config();  ///for softuart
///   SoftUartInit(0,SOFT_TX_GPIO,SOFT_TX_PIN
///                  ,SOFT_RX_GPIO,SOFT_RX_PIN);
///    SoftUartEnableRx(0);
///============================================
////    SoftUARTFunc.Init(9600);
#if 0
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

////    USARTx_CFG();
///    IIC_Init( 100000, RXAdderss ); // 100Kbps
///    I2C1->CTLR1 |= 0x0080; // CTLR1_NOSTRETCH_Set - Disable clock stretching
///   I2C1->CTLR1 |= 0x0400; // CTLR1_ACK_Set - Enable ACK following each byte received - This also stops the clock stretching for each character received.

  ///  TIM2_Config();  ///for adc

 while(1)
    {
     tst++;
     set_led(tst);
     Delay_Ms(300);

////    printf("cur_adc_dat:%d\r\n",cur_adc_dat);
    t_rez=read_encoder_val(&rdat);
    if(t_rez==0){
      if(prev_enc!=rdat){
          prev_enc=rdat;
          printf( "enc:%04x\r\n",rdat);
       }
    }

 ///    send_char_suart(0x35);
  ///    SoftUartTransmitBit(&SUart[0],tst&0x1);

///     SoftUARTFunc.TransmitBytes(tmp, 4);
/*
         rdat= I2C_ReadRegister(I2C1, I2C_Register_DATAR);
         if(prev_adc!=rdat){
             prev_adc=rdat;
             printf( "adc:%04x\r\n",rdat);
          }
  */

    }
}
///===================================================================
