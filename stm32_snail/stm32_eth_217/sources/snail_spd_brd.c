

#include "snail_spd_brd.h"

void gpio_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
///============= LEDS =========================
RCC_AHB1PeriphClockCmd(LED0_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = LED0_PIN;
GPIO_Init(LED0_GPIO, &GPIO_InitStructure);
////GPIO_SetBits(LED0_GPIO, LED0_PIN);

RCC_AHB1PeriphClockCmd(LED1_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = LED1_PIN;
GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
////GPIO_SetBits(LED1_GPIO, LED1_PIN);

RCC_AHB1PeriphClockCmd(LED2_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = LED2_PIN;
GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
////GPIO_SetBits(LED2_GPIO, LED2_PIN);

RCC_AHB1PeriphClockCmd(LED3_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = LED3_PIN;
GPIO_Init(LED3_GPIO, &GPIO_InitStructure);
////GPIO_SetBits(LED3_GPIO, LED3_PIN);

#if 0
////EXTI_InitTypeDef EXTI_InitStructure;
////NVIC_InitTypeDef NVIC_InitStructure;
///=============psk pin =========================
RCC_AHB1PeriphClockCmd(UTRK_PSK_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = UTRK_PSK_PIN;
GPIO_Init(UTRK_PSK_GPIO, &GPIO_InitStructure);
GPIO_SetBits(UTRK_PSK_GPIO, UTRK_PSK_PIN);
///=============irq pin =========================
RCC_AHB1PeriphClockCmd(UTRK_IRQ_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = UTRK_IRQ_PIN;
GPIO_Init(UTRK_IRQ_GPIO, &GPIO_InitStructure);
#if 0
/* Connect  EXTI Line to GPIO Pin */
SYSCFG_EXTILineConfig(UTRK_IRQ_EXTI_PORT, UTRK_IRQ_EXTI_PIN);
/* Configure  EXTI line */
EXTI_InitStructure.EXTI_Line = UTRK_IRQ_EXTI_LINE;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);
/* Enable and set EXTI Interrupt to the lowest priority */
NVIC_InitStructure.NVIC_IRQChannel = UTRK_IRQ_EXTI_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure); 
#endif
///====== done fpga =====================
RCC_AHB1PeriphClockCmd(FPGA_DONE_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_DONE_PIN;
GPIO_Init(FPGA_DONE_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_DONE_GPIO, FPGA_DONE_PIN);
///============= Z0 =========================
////RCC_AHB1PeriphClockCmd(TST_Z0_RCC_AHB,ENABLE);
////GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
////GPIO_InitStructure.GPIO_Pin   = TST_Z0_PIN;
////GPIO_Init(TST_Z0_GPIO, &GPIO_InitStructure);

///============= FPGA_RESET =========================
RCC_AHB1PeriphClockCmd(FPGA_RESET_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = FPGA_RESET_PIN;
GPIO_SetBits(FPGA_RESET_GPIO, FPGA_RESET_PIN);
GPIO_Init(FPGA_RESET_GPIO, &GPIO_InitStructure);
GPIO_SetBits(FPGA_RESET_GPIO, FPGA_RESET_PIN);
///============= NCLR_FPGA =========================
RCC_AHB1PeriphClockCmd(NCLR_FPGA_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Pin   = NCLR_FPGA_PIN;
GPIO_Init(NCLR_FPGA_GPIO, &GPIO_InitStructure);
GPIO_SetBits(NCLR_FPGA_GPIO, NCLR_FPGA_PIN);
///============= Z1 =========================
RCC_AHB1PeriphClockCmd(TST_Z1_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = TST_Z1_PIN;
GPIO_Init(TST_Z1_GPIO, &GPIO_InitStructure);
#if 0
///============= Z2 MCO_1 ========================
RCC_AHB1PeriphClockCmd(TST_Z2_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Pin   = TST_Z2_PIN;
GPIO_Init(TST_Z2_GPIO, &GPIO_InitStructure);
GPIO_PinAFConfig(TST_Z2_GPIO, TST_Z2_SOURCE, GPIO_AF_MCO);
#endif
#if 0
///============= Z2 =========================
RCC_AHB1PeriphClockCmd(TST_Z2_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = TST_Z2_PIN;
GPIO_Init(TST_Z2_GPIO, &GPIO_InitStructure);
#else
///============= NCS_FLASH =========================
RCC_AHB1PeriphClockCmd(NCS_FLASH_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = NCS_FLASH_PIN;
GPIO_SetBits(NCS_FLASH_GPIO, NCS_FLASH_PIN);
GPIO_Init(NCS_FLASH_GPIO, &GPIO_InitStructure);
GPIO_SetBits(NCS_FLASH_GPIO, NCS_FLASH_PIN);
#endif
///============= Z3 =========================
RCC_AHB1PeriphClockCmd(TST_Z3_RCC_AHB,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_Pin   = TST_Z3_PIN;
GPIO_Init(TST_Z3_GPIO, &GPIO_InitStructure);
#endif
}
////=========================================
void put_led0(uint8_t idata)
{
if(idata&0x1)
  LED0_GPIO->BSRRL= LED0_PIN;
else
  LED0_GPIO->BSRRH= LED0_PIN;
}
void put_led1(uint8_t idata)
{
if(idata&0x1)
  LED1_GPIO->BSRRL= LED1_PIN;
else
  LED1_GPIO->BSRRH= LED1_PIN;
}
void put_led2(uint8_t idata)
{
if(idata&0x1)
  LED2_GPIO->BSRRL= LED2_PIN;
else
  LED2_GPIO->BSRRH= LED2_PIN;
}
void put_led3(uint8_t idata)
{
if(idata&0x1)
  LED3_GPIO->BSRRL= LED3_PIN;
else
  LED3_GPIO->BSRRH= LED3_PIN;
}

////=========================================
void uDelay (const uint32_t usec)
{
uint32_t count = 0;
const uint32_t utime = 120*usec;////(120 * usec / 7);
do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);
}
////==================================
void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;


  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(CAN2_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_RX_SOURCE, CAN1_AF_PORT);
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_TX_SOURCE, CAN1_AF_PORT);

  GPIO_PinAFConfig(CAN2_GPIO_PORT, CAN2_RX_SOURCE, CAN2_AF_PORT);
  GPIO_PinAFConfig(CAN2_GPIO_PORT, CAN2_TX_SOURCE, CAN2_AF_PORT);


  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);



  /* Configure CAN RX and TX pins */
   GPIO_InitStructure.GPIO_Pin = CAN2_RX_PIN | CAN2_TX_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(CAN2_GPIO_PORT, &GPIO_InitStructure);


  /* CAN configuration ********************************************************/
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);
  RCC_APB1PeriphClockCmd(CAN2_CLK, ENABLE);

  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_DeInit(CAN2);

  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

  /* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN1, &CAN_InitStructure);


  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

  /* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN2, &CAN_InitStructure);




  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  //CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO1;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  //CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);





//  CAN2TxMessage.StdId = 0x321;
//  CAN2TxMessage.ExtId = 0x01;
//  CAN2TxMessage.RTR = CAN_RTR_DATA;
//  CAN2TxMessage.IDE = CAN_ID_STD;
//  CAN2TxMessage.DLC = 8;

  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
  CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);

}



////==================================




