
#include "cam_can_brd.h"

uint8_t cur_stat=0;

//=========== tim_pwm ======================================
void TIM_PWM_set_val( uint16_t ccp )
{
 TIM_PWM->CH1CVR = ccp;
}
/*********************************************************************
 * @fn      TIM1_OutCompare_Init
 *
 * @brief   Initializes TIM1 output compare.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM_PWMOut_Init( uint16_t arr, uint16_t psc, uint16_t ccp )
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8, ENABLE );

    GPIO_InitStructure.GPIO_Pin = PWM_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( PWM_LED_GPIO, &GPIO_InitStructure );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM_PWM, &TIM_TimeBaseInitStructure);

#if (PWM_MODE == PWM_MODE1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

#elif (PWM_MODE == PWM_MODE2)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

#endif

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init( TIM_PWM, &TIM_OCInitStructure );

    TIM_CtrlPWMOutputs(TIM_PWM, ENABLE );
    TIM_OC1PreloadConfig( TIM_PWM, TIM_OCPreload_Disable );
    TIM_ARRPreloadConfig( TIM_PWM, ENABLE );
    TIM_Cmd( TIM_PWM, ENABLE );
}
///======= gpio ============================================
void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE );
   ////============= PWM_LED ==================================
    GPIO_InitStructure.GPIO_Pin = PWM_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PWM_LED_GPIO, &GPIO_InitStructure);

    ////============= ON_DV ==================================
    GPIO_InitStructure.GPIO_Pin = ON_DV_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ON_DV_GPIO, &GPIO_InitStructure);
    ////============= CAN ==================================
    GPIO_PinRemapConfig( GPIO_Remap_CAN2, DISABLE);

    GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( CAN_TX_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( CAN_RX_GPIO, &GPIO_InitStructure);
   ////============= INH ==================================
    GPIO_InitStructure.GPIO_Pin = INH_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(INH_GPIO, &GPIO_InitStructure);
    GPIO_ResetBits(INH_GPIO, INH_PIN);

    ////=============led ==================================

    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO, &GPIO_InitStructure);
    ////=============tst1 ==================================
    GPIO_InitStructure.GPIO_Pin = TST1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TST1_GPIO, &GPIO_InitStructure);
    ////=============tst2 ==================================
    GPIO_InitStructure.GPIO_Pin = TST2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TST2_GPIO, &GPIO_InitStructure);
    ////=============tst3 ==================================
     GPIO_InitStructure.GPIO_Pin = TST3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TST3_GPIO, &GPIO_InitStructure);
}

extern void init_can(void);
void board_init(void)
{
gpio_init();
TIM_PWMOut_Init(DEF_PER, DEF_PRESC, DEF_VAL );
init_can();

/* Bps = 250Kbps */
////CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );

}
////=============INH ==================================
void set_inh(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(INH_GPIO,INH_PIN,Bit_SET);
 else
     GPIO_WriteBit(INH_GPIO,INH_PIN, Bit_RESET);
}
////=============ON_DV ==================================
void on_off_dv(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(ON_DV_GPIO,ON_DV_PIN,Bit_SET);
 else
     GPIO_WriteBit(ON_DV_GPIO,ON_DV_PIN, Bit_RESET);
}
///=============== led =======================================
void set_led(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(LED_GPIO,LED_PIN,Bit_SET);
 else
     GPIO_WriteBit(LED_GPIO,LED_PIN, Bit_RESET);
}
///=============== tst1 =======================================
void set_tst1(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(TST1_GPIO,TST1_PIN,Bit_SET);
 else
     GPIO_WriteBit(TST1_GPIO,TST1_PIN, Bit_RESET);
}
///=============== tst2 =======================================
void set_tst2(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(TST2_GPIO,TST2_PIN,Bit_SET);
 else
     GPIO_WriteBit(TST2_GPIO,TST2_PIN, Bit_RESET);
}
///=============== tst1 =======================================
void set_tst3(uint8_t on_off)
{
 if(on_off&0x1)
     GPIO_WriteBit(TST3_GPIO,TST3_PIN,Bit_SET);
 else
     GPIO_WriteBit(TST3_GPIO,TST3_PIN, Bit_RESET);
}

///=============== led pwm =======================================
void set_led_pwm(uint16_t led_pwm)
{
    TIM_PWM_set_val(led_pwm);
}

#if 0
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 i = 0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    printf("GPIO Toggle TEST\r\n");
    GPIO_Toggle_INIT();

    while(1)
    {
        Delay_Ms(250);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
#endif
