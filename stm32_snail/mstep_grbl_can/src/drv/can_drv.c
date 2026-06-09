#include "stdint.h"
#include "stm32f2xx.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_can.h"
#include "misc.h"
#include "board.h"
#include "can.h"

#define MAX_CAN_DATA_LEN 8
#define ID_MASTER_CMD    (0x1U << 9)

uint8_t  CAN_TxRdy = 0;
uint8_t  CAN_RxRdy = 0;
can_msg_t CAN_RxMsg;

static can_br_coef_t can_br_coef_tab[] = {
  {150, CAN_BS1_15tq, CAN_BS2_5tq},
  {75,  CAN_BS1_15tq, CAN_BS2_5tq},
  {30,  CAN_BS1_15tq, CAN_BS2_5tq},
  {30,  CAN_BS1_8tq,  CAN_BS2_2tq},
  {15,  CAN_BS1_14tq, CAN_BS2_2tq},
  {15,  CAN_BS1_7tq,  CAN_BS2_1tq},
  {6,   CAN_BS1_7tq,  CAN_BS2_2tq},
  {3,   CAN_BS1_11tq, CAN_BS2_2tq},
  {2,   CAN_BS1_13tq, CAN_BS2_2tq}
};

static void NVIC_can_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void can_filter_config(uint8_t num, uint32_t id, uint32_t mask)
{
  CAN_FilterInitTypeDef CAN_FilterInitStructure;

  CAN_FilterInitStructure.CAN_FilterNumber = num;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = (uint16_t)((id >> 16) & 0xffffU);
  CAN_FilterInitStructure.CAN_FilterIdLow = (uint16_t)(id & 0xffffU);
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (uint16_t)((mask >> 16) & 0xffffU);
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = (uint16_t)(mask & 0xffffU);
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
}

static void canfilter_master_init(void)
{
  uint32_t id = ID_MASTER_CMD << 21;
  uint32_t mask = ID_MASTER_CMD << 21;

  can_filter_config(0, id, mask);
}

static int can_init(FunctionalState ttcm, FunctionalState abom, FunctionalState awum,
                    FunctionalState nart, FunctionalState rflm, FunctionalState txfp,
                    uint32_t sjw, uint32_t ts1, uint32_t ts2, uint32_t brp,
                    uint8_t loopback, uint8_t silent)
{
  CAN_InitTypeDef CAN_InitStructure;
  uint8_t mode = 0;

  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);
  CAN_InitStructure.CAN_TTCM = ttcm;
  CAN_InitStructure.CAN_ABOM = abom;
  CAN_InitStructure.CAN_AWUM = awum;
  CAN_InitStructure.CAN_NART = nart;
  CAN_InitStructure.CAN_RFLM = rflm;
  CAN_InitStructure.CAN_TXFP = txfp;
  if (loopback) {
    mode |= CAN_Mode_LoopBack;
  }
  if (silent) {
    mode |= CAN_Mode_Silent;
  }
  CAN_InitStructure.CAN_Mode = mode;
  CAN_InitStructure.CAN_SJW = sjw;
  CAN_InitStructure.CAN_Prescaler = brp;
  CAN_InitStructure.CAN_BS1 = ts1;
  CAN_InitStructure.CAN_BS2 = ts2;

  return (CAN_Init(CAN1, &CAN_InitStructure) == CAN_InitStatus_Success) ? 0 : -1;
}

static int can_speed(uint8_t index)
{
  if (index >= MAX_NUM_BR) {
    return -1;
  }
  return can_init(DISABLE, DISABLE, DISABLE, ENABLE,
                  DISABLE, DISABLE, CAN_SJW_1tq,
                  can_br_coef_tab[index].ts1, can_br_coef_tab[index].ts2,
                  can_br_coef_tab[index].pre, _FALSE, _FALSE);
}

void CAN_rdMsg(can_msg_t *msg)
{
  if ((CAN1->sFIFOMailBox[0].RIR & CAN_ID_EXT) == 0) {
    msg->format = STANDARD_FORMAT;
    msg->id     = 0x000007FFU & (CAN1->sFIFOMailBox[0].RIR >> 21);
  } else {
    msg->format = EXTENDED_FORMAT;
    msg->id     = 0x1FFFFFFFU & (CAN1->sFIFOMailBox[0].RIR >> 3);
  }

  if ((CAN1->sFIFOMailBox[0].RIR & CAN_RTR_REMOTE) == 0) {
    msg->type = DATA_FRAME;
  } else {
    msg->type = REMOTE_FRAME;
  }

  msg->len = (CAN1->sFIFOMailBox[0].RDTR) & 0x0FU;
  msg->data[0] = (CAN1->sFIFOMailBox[0].RDLR      ) & 0xFFU;
  msg->data[1] = (CAN1->sFIFOMailBox[0].RDLR >>  8) & 0xFFU;
  msg->data[2] = (CAN1->sFIFOMailBox[0].RDLR >> 16) & 0xFFU;
  msg->data[3] = (CAN1->sFIFOMailBox[0].RDLR >> 24) & 0xFFU;
  msg->data[4] = (CAN1->sFIFOMailBox[0].RDHR      ) & 0xFFU;
  msg->data[5] = (CAN1->sFIFOMailBox[0].RDHR >>  8) & 0xFFU;
  msg->data[6] = (CAN1->sFIFOMailBox[0].RDHR >> 16) & 0xFFU;
  msg->data[7] = (CAN1->sFIFOMailBox[0].RDHR >> 24) & 0xFFU;

  CAN1->RF0R |= CAN_RF0R_RFOM0;
}

void CAN_wrMsg(can_msg_t *msg)
{
  CAN1->sTxMailBox[0].TIR = 0;

  if (msg->format == STANDARD_FORMAT) {
    CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id << 21) | CAN_ID_STD;
  } else {
    CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id << 3) | CAN_ID_EXT;
  }

  if (msg->type == DATA_FRAME) {
    CAN1->sTxMailBox[0].TIR |= CAN_RTR_DATA;
  } else {
    CAN1->sTxMailBox[0].TIR |= CAN_RTR_REMOTE;
  }

  CAN1->sTxMailBox[0].TDLR = (((uint32_t)msg->data[3] << 24) |
                              ((uint32_t)msg->data[2] << 16) |
                              ((uint32_t)msg->data[1] <<  8) |
                              ((uint32_t)msg->data[0]));
  CAN1->sTxMailBox[0].TDHR = (((uint32_t)msg->data[7] << 24) |
                              ((uint32_t)msg->data[6] << 16) |
                              ((uint32_t)msg->data[5] <<  8) |
                              ((uint32_t)msg->data[4]));

  CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
  CAN1->sTxMailBox[0].TDTR |= (msg->len & CAN_TDT0R_DLC);

  CAN_TxRdy = 0;
  CAN1->IER |= CAN_IER_TMEIE;
  CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;
}

void CAN1_RX0_IRQHandler(void)
{
  if (CAN1->RF0R & CAN_RF0R_FMP0) {
    CAN_rdMsg(&CAN_RxMsg);
    CAN_RxRdy = 1;
  }
}

void CAN1_RX1_IRQHandler(void)
{
  if (CAN1->RF1R & CAN_RF1R_FMP1) {
    CAN_rdMsg(&CAN_RxMsg);
    CAN_RxRdy = 1;
  }
}

void CAN1_TX_IRQHandler(void)
{
  if (CAN1->TSR & CAN_TSR_RQCP0) {
    CAN1->TSR |= CAN_TSR_RQCP0;
    CAN1->IER &= ~CAN_IER_TMEIE;
    CAN_TxRdy = 1;
  }
}

void can1_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(CAN1_INH_PIN_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = CAN1_INH_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(CAN1_INH_PIN_GPIO, &GPIO_InitStructure);
  GPIO_ResetBits(CAN1_INH_PIN_GPIO, CAN1_INH_PIN);

  RCC_AHB1PeriphClockCmd(CAN1_RX_PIN_RCC, ENABLE);
  GPIO_PinAFConfig(CAN1_RX_PIN_GPIO, CAN1_RX_PIN_SOURCE, GPIO_AF_CAN1);
  GPIO_PinAFConfig(CAN1_TX_PIN_GPIO, CAN1_TX_PIN_SOURCE, GPIO_AF_CAN1);

  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(CAN1_RX_PIN_GPIO, &GPIO_InitStructure);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  can_init(DISABLE, DISABLE, DISABLE, ENABLE,
           DISABLE, DISABLE, CAN_SJW_1tq, CAN_BS1_6tq, CAN_BS2_8tq,
           4, _FALSE, _FALSE);
  can_speed(DEF_CAN_BR);

  NVIC_can_Config();
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
  CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
  canfilter_master_init();

  CAN_RxRdy = 0;
  CAN_TxRdy = 1;
}

uint8_t can1_send(uint16_t id, uint8_t data_len, uint8_t *data)
{
  can_msg_t msg;
  uint8_t ii;

  if (data_len > MAX_CAN_DATA_LEN) {
    data_len = MAX_CAN_DATA_LEN;
  }

  msg.id = id;
  msg.len = data_len;
  msg.format = STANDARD_FORMAT;
  msg.type = DATA_FRAME;
  for (ii = 0; ii < data_len; ii++) {
    msg.data[ii] = data[ii];
  }

  CAN_wrMsg(&msg);
  return data_len;
}
