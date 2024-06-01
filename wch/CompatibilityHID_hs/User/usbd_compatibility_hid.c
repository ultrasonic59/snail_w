/********************************** (C) COPYRIGHT *******************************
 * File Name  :usbd_compatibility_hid.c
 * Author     :OWNER
 * Version    : v0.01
 * Date       : 2022Äê7ÔÂ8ÈÕ
 * Description:
*******************************************************************************/
#include "ch32v30x_usbhs_device.h"
#include "usbd_compatibility_hid.h"
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

////__attribute__ ((aligned(4))) uint8_t UART2_RxBuffer[DEF_UART2_BUF_SIZE];  // UART2 Rx Buffer
__attribute__ ((aligned(4))) uint8_t  HID_Report_Buffer[DEF_USBD_HS_PACK_SIZE];              // HID Report Buffer
volatile uint8_t HID_Set_Report_Flag = SET_REPORT_DEAL_OVER;               // HID SetReport flag

#if 0
volatile uint16_t UART2_TimeOut;                                           // UART2 RX timeout flag
volatile uint8_t  UART2_Tx_Flag = 0;                                       // UART2 TX flag

volatile uint16_t UART2_RX_CurCnt = 0;                                     // UART2 DMA current remain count
volatile uint16_t UART2_RX_LastCnt = 0;                                    // UART2 DMA last remain count
volatile uint16_t UART2_Rx_RemainLen = 0;                                  // UART2 RX data remain len
volatile uint16_t UART2_Rx_Deal_Ptr = 0;                                   // UART2 RX data deal pointer
#endif
volatile uint16_t Data_Pack_Max_Len = 0;                                   // UART data packet length in hid packet
volatile uint16_t _Head_Pack_Len = 0;                                       // UART head packet( valid data length ) length in hid packet

/*********************************************************************
 * @fn      TIM2_Init
 *
 * @brief   Timer2 100us initialisation
 *
 * @return  none
 */
void TIM2_Init( void )
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 71;
    TIM_TimeBaseStructure.TIM_Prescaler =100;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

/*********************************************************************
 * @fn      TIM2_IRQHandler
 *
 * @brief   TIM2 IRQ handler
 *
 * @return  none
 */
void TIM2_IRQHandler(void)
{
/////    UART2_TimeOut++;
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}



/*********************************************************************
 * @fn      UART2_Rx_Service
 *
 * @brief   UART2 rx service routine that sends the data received by
 *          uart2 via USB-HID.
 *
 * @return  none
 */
void UART2_Rx_Service( void )
{
#if 0
    uint16_t pkg_len;
    uint16_t u16_temp;
    uint16_t remain_len;

    /* Get uart2 rx data */
    UART2_RX_CurCnt = DMA_GetCurrDataCounter(DMA1_Channel6);    // Get DMA remaining count
    if (UART2_RX_LastCnt != UART2_RX_CurCnt)
    {
        if (UART2_RX_LastCnt > UART2_RX_CurCnt)
        {
            u16_temp = UART2_RX_LastCnt - UART2_RX_CurCnt;
        }
        else
        {
            u16_temp = UART2_RX_LastCnt + ( DEF_UART2_BUF_SIZE - UART2_RX_CurCnt );
        }

        UART2_RX_LastCnt = UART2_RX_CurCnt;

        if ((UART2_Rx_RemainLen + u16_temp) > DEF_UART2_BUF_SIZE )
        {
            printf("Uart2 RX_buffer overflow\n");                                           // overflow: New data overwrites old data
        }
        else
        {
            UART2_Rx_RemainLen += u16_temp;
        }
        UART2_TimeOut = 0;
    }

    /* Pass-through uart2 data to USB-HID  */
    if (UART2_Rx_RemainLen)
    {
        /* Determine if the USB endpoint is allowed to upload */
        if ( USBHS_Endp_Busy[ 2 ] == 0x00)
        {
            /* Calculate the length of this packet upload via USB. */
            remain_len = UART2_Rx_RemainLen;
            pkg_len = 0x00;

            if (remain_len >= Data_Pack_Max_Len)
            {
                remain_len = Data_Pack_Max_Len;
                pkg_len = remain_len;
            }
            else
            {
                if (UART2_TimeOut > DEF_UART2_TOUT_TIME)
                {
                    pkg_len = remain_len;
                }
            }

            if ( pkg_len > ( DEF_UART2_BUF_SIZE - UART2_Rx_Deal_Ptr )  )
            {
                pkg_len = ( DEF_UART2_BUF_SIZE - UART2_Rx_Deal_Ptr );                       // The data at the end of the buffer will be sent directly.
            }

            /* Upload packet via USB. */
            if (pkg_len)
            {
                USBHS_EP2_Tx_Buf[0] = (uint8_t)pkg_len;
                if (USBHS_DevSpeed == USBHS_SPEED_HIGH)
                {
                    USBHS_EP2_Tx_Buf[1] = (uint8_t)(pkg_len >> 8) ;
                }
                memcpy(USBHS_EP2_Tx_Buf + _Head_Pack_Len,&UART2_RxBuffer[UART2_Rx_Deal_Ptr],pkg_len);
                USBHSD->UEP2_TX_DMA  = (uint32_t)(uint8_t *)USBHS_EP2_Tx_Buf;
                USBHSD->UEP2_TX_LEN  = pkg_len + _Head_Pack_Len;
                USBHS_Endp_Busy[ 2 ] |= DEF_UEP_BUSY;
                USBHSD->UEP2_TX_CTRL = ((USBHSD->UEP2_TX_CTRL) & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
                UART2_Rx_RemainLen -= pkg_len;
                UART2_Rx_Deal_Ptr += pkg_len;
                if (UART2_Rx_Deal_Ptr >= DEF_UART2_BUF_SIZE)
                {
                    UART2_Rx_Deal_Ptr = 0x00;
                }

            }
        }
    }
#endif
}

/*********************************************************************
 * @fn      UART2_Tx_Service
 *
 * @brief   UART2 tx service routine that sends the data received by
 *          USB-HID via uart2.
 *
 * @return  none
 */
void UART2_Tx_Service( void )
{
 uint16_t pkg_len = 0;
 uint8_t *pbuf;
 if(RingBuffer_Comm._RemainPack)
  {
  printf( "dat[%x:%x]\r\n",Data_Buffer[0],Data_Buffer[1]) ;

  RingBuffer_Comm._RemainPack--;
 ///============================================================================
  USBHSD->UEP1_RX_CTRL = (USBHSD->UEP1_RX_CTRL & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_ACK;
///==============================================================================

////  if(Data_Buffer[0]==0x3) ///read data
      {
      printf( "rd data\r\n") ;
     USBHS_EP2_Tx_Buf[0] = 1;
      USBHS_EP2_Tx_Buf[1] = 0;
      USBHS_EP2_Tx_Buf[2] = 0x35;

 ////      if (USBHS_DevSpeed == USBHS_SPEED_HIGH)
 ////      {
 ////          USBHS_EP2_Tx_Buf[1] = (uint8_t)(pkg_len >> 8) ;
 ////      }
 ////      memcpy(USBHS_EP2_Tx_Buf + 2,&UART2_RxBuffer[UART2_Rx_Deal_Ptr],3);
       USBHSD->UEP2_TX_DMA  = (uint32_t)(uint8_t *)USBHS_EP2_Tx_Buf;
       USBHSD->UEP2_TX_LEN  = 3;
       USBHS_Endp_Busy[ 2 ] |= DEF_UEP_BUSY;
       USBHSD->UEP2_TX_CTRL = ((USBHSD->UEP2_TX_CTRL) & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
      }
  }
#if 0
    if (UART2_Tx_Flag)
    {
        if (USART_GetFlagStatus(USART2, USART_FLAG_TC))                                  // Check whether uart2 has finished sending.
        {
            USART_ClearFlag(USART2, USART_FLAG_TC);
            USART_DMACmd(USART2, USART_DMAReq_Tx, DISABLE);
            UART2_Tx_Flag = 0;
            NVIC_DisableIRQ(USBHS_IRQn);                                                  // Disable USB interrupts
            RingBuffer_Comm.RemainPack--;
            RingBuffer_Comm.DealPtr++;
            if(RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
            {
                RingBuffer_Comm.DealPtr = 0;
            }
            NVIC_EnableIRQ(USBHS_IRQn);                                                   // Enable USB interrupts
        }
    }
    else
    {
        /* Pass-through USB-HID data to uart2 */
        if(RingBuffer_Comm.RemainPack)
        {
            if ( USBHS_DevSpeed == USBHS_SPEED_HIGH )
            {
                pkg_len = *(uint16_t*)&Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_HS_PACK_SIZE];      // Get the valid data length
            }
            else
            {
                pkg_len = (uint16_t)Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_HS_PACK_SIZE];                   // Get the valid data length
            }
            if (pkg_len)
            {
                if (pkg_len > Data_Pack_Max_Len )
                {
                    pkg_len = Data_Pack_Max_Len;                                                        // Limit the length of this transmission
                }
                pbuf = &Data_Buffer[(RingBuffer_Comm.DealPtr) * DEF_USBD_HS_PACK_SIZE] + Head_Pack_Len;
                UART2_DMA_Tx( pbuf, pkg_len );
                UART2_Tx_Flag = 1;
            }
            else
            {
                /* drop out */
                NVIC_DisableIRQ(USBHS_IRQn);                                                  // Disable USB interrupts
                RingBuffer_Comm.RemainPack--;
                RingBuffer_Comm.DealPtr++;
                if(RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
                {
                    RingBuffer_Comm.DealPtr = 0;
                }
                NVIC_EnableIRQ(USBHS_IRQn);                                                   // Enable USB interrupts
            }

        }
    }
#endif
#if 0
    /* Monitor whether the remaining space is available for further downloads */
    if(RingBuffer_Comm.RemainPack < (DEF_Ring_Buffer_Max_Blks - DEF_RING_BUFFER_RESTART))
    {
        if(RingBuffer_Comm.StopFlag)
        {
            RingBuffer_Comm.StopFlag = 0;
            USBHSD->UEP1_RX_CTRL = (USBHSD->UEP1_RX_CTRL & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_ACK;
        }
    }
#endif

}

/*********************************************************************
 * @fn      HID_Set_Report_Deal
 *
 * @brief   print hid set report data
 *
 * @return  none
 */
void HID_Set_Report_Deal()
{
    uint16_t i;
    if (HID_Set_Report_Flag == SET_REPORT_WAIT_DEAL)
    {
        printf("Set Report:\n");
        for (i = 0; i < USBHS_DevMaxPackLen; ++i)
        {
            printf("%02x ",HID_Report_Buffer[i]);
        }
        printf("\n");
        HID_Set_Report_Flag = SET_REPORT_DEAL_OVER;
        USBHSD->UEP0_TX_LEN = 0;
        USBHSD->UEP0_TX_CTRL = (USBHSD->UEP0_TX_CTRL & USBHS_UEP_T_TOG_MASK) | USBHS_UEP_T_RES_ACK;

    }
}




