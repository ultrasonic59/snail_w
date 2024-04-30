
#include "cam_can_brd.h"

uint8_t cur_stat=0;

//=========== tim_pwm ======================================
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
/*********************************************************************
 * @fn      CAN_Mode_Init
 *
 * @brief   Initializes CAN communication test mode.
 *          Bps =Fpclk1/((tpb1+1+tbs2+1+1)*brp)
 *
 * @param   tsjw - CAN synchronisation jump width.
 *          tbs2 - CAN time quantum in bit segment 1.
 *          tbs1 - CAN time quantum in bit segment 2.
 *          brp - Specifies the length of a time quantum.
 *          mode - Test mode.
 *            CAN_Mode_Normal.
 *            CAN_Mode_LoopBack.
 *            CAN_Mode_Silent.
 *            CAN_Mode_Silent_LoopBack.
 *
 * @return  none
 */
void CAN_Mode_Init( u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode )
{
    GPIO_InitTypeDef GPIO_InitSturcture={0};
    CAN_InitTypeDef CAN_InitSturcture={0};
    CAN_FilterInitTypeDef CAN_FilterInitSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE );

    GPIO_PinRemapConfig( GPIO_Remap1_CAN1, ENABLE);

    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitSturcture);

    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( GPIOB, &GPIO_InitSturcture);

    CAN_InitSturcture.CAN_TTCM = DISABLE;
    CAN_InitSturcture.CAN_ABOM = DISABLE;
    CAN_InitSturcture.CAN_AWUM = DISABLE;
    CAN_InitSturcture.CAN_NART = ENABLE;
    CAN_InitSturcture.CAN_RFLM = DISABLE;
    CAN_InitSturcture.CAN_TXFP = DISABLE;
    CAN_InitSturcture.CAN_Mode = mode;
    CAN_InitSturcture.CAN_SJW = tsjw;
    CAN_InitSturcture.CAN_BS1 = tbs1;
    CAN_InitSturcture.CAN_BS2 = tbs2;
    CAN_InitSturcture.CAN_Prescaler = brp;
    CAN_Init( CAN1, &CAN_InitSturcture );

    CAN_FilterInitSturcture.CAN_FilterNumber = 0;

#if (Frame_Format == Standard_Frame)
/* identifier/mask mode, One 32-bit filter, StdId: 0x317 */
    CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
    CAN_FilterInitSturcture.CAN_FilterIdLow = 0;
    CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0xFFE0;
    CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x0006;

/* identifier/mask mode, Two 16-bit filters, StdId: 0x317£¬0x316 */
//  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_16bit;
//  CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//  CAN_FilterInitSturcture.CAN_FilterIdLow = 0xFFF8;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x62C0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0xFFF8;

/* identifier list mode, One 32-bit filter, StdId: 0x317£¬0x316 */
//  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdList;
//  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//  CAN_FilterInitSturcture.CAN_FilterIdLow = 0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x62C0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0;

/* identifier list mode, Two 16-bit filters, StdId: 0x317,0x316,0x315,0x314 */
//  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdList;
//  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_16bit;
//  CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//  CAN_FilterInitSturcture.CAN_FilterIdLow = 0x62C0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x62A0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x6280;

#elif (Frame_Format == Extended_Frame)
/* identifier/mask mode, One 32-bit filter, ExtId: 0x12124567 */
    CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x9092;
    CAN_FilterInitSturcture.CAN_FilterIdLow = 0x2B3C;
    CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0xFFFE;

#endif

    CAN_FilterInitSturcture.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitSturcture.CAN_FilterActivation = ENABLE;
    CAN_FilterInit( &CAN_FilterInitSturcture );
}
/*********************************************************************
 * @fn      CAN_Send_Msg
 *
 * @brief   CAN Transmit function.
 *
 * @param   msg - Transmit data buffer.
 *          len - Data length.
 *
 * @return  0 - Send successful.
 *          1 - Send failed.
 */
u8 CAN_Send_Msg( u8 *msg, u8 len )
{
    u8 mbox;
    u16 i = 0;

    CanTxMsg CanTxStructure;

#if (Frame_Format == Standard_Frame)
    CanTxStructure.StdId = 0x317;
    CanTxStructure.IDE = CAN_Id_Standard;

#elif (Frame_Format == Extended_Frame)
    CanTxStructure.ExtId = 0x12124567;
    CanTxStructure.IDE = CAN_Id_Extended;

#endif

    CanTxStructure.RTR = CAN_RTR_Data;
    CanTxStructure.DLC = len;

    for( i=0; i<len; i++ )
    {
        CanTxStructure.Data[i] = msg[i];
    }

    mbox = CAN_Transmit( CAN1, &CanTxStructure);
    i = 0;

    while( ( CAN_TransmitStatus( CAN1, mbox ) != CAN_TxStatus_Ok ) && (i < 0xFFF) )
    {
        i++;
    }

    if( i == 0xFFF )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*********************************************************************
 * @fn      CAN_Receive_Msg
 *
 * @brief   CAN Receive function.
 *
 * @param   buf - Receive data buffer.
 *          len - Data length.
 *
 * @return  CanRxStructure.DLC - Receive data length.
 */
u8 CAN_Receive_Msg( u8 *buf )
{
    u8 i;

    CanRxMsg CanRxStructure;

    if( CAN_MessagePending( CAN1, CAN_FIFO0 ) == 0)
    {
        return 0;
    }

    CAN_Receive( CAN1, CAN_FIFO0, &CanRxStructure );

    for( i=0; i<8; i++ )
    {
        buf[i] = CanRxStructure.Data[i];
    }

    return CanRxStructure.DLC;
}


///======= gpio ============================================
void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
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
