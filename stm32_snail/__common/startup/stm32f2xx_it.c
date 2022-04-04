/**
  ******************************************************************************
  * @file    stm32f2xx_it.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    06-June-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f2xx_it.h"
#include "stm32f2xx_can.h"

extern void vPortSVCHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void usart1_irq(void);
extern void usart2_irq(void);


/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}


void hard_fault_handler_c (unsigned int * hardfault_args)
{
#if 1
  volatile unsigned int stacked_r0;
  volatile unsigned int stacked_r1;
  volatile unsigned int stacked_r2;
  volatile unsigned int stacked_r3;
  volatile unsigned int stacked_r12;
  volatile unsigned int stacked_lr;
  volatile unsigned int stacked_pc;
  volatile unsigned int stacked_psr;
 
  stacked_r0 = ((unsigned long) hardfault_args[0]);
  stacked_r1 = ((unsigned long) hardfault_args[1]);
  stacked_r2 = ((unsigned long) hardfault_args[2]);
  stacked_r3 = ((unsigned long) hardfault_args[3]);
 
  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr = ((unsigned long) hardfault_args[5]);
  stacked_pc = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);
#endif
 while (1);
#if 0
  printf ("\r\n\r\n[Hard fault handler - all numbers in hex]\r\n");
  printf ("R0 = %x\r\n", stacked_r0);
  printf ("R1 = %x\r\n", stacked_r1);
  printf ("R2 = %x\r\n", stacked_r2);
  printf ("R3 = %x\r\n", stacked_r3);
  printf ("R12 = %x\r\n", stacked_r12);
  printf ("LR [R14] = %x  subroutine call return address\r\n", stacked_lr);
  printf ("PC [R15] = %x  program counter\r\n", stacked_pc);
  printf ("PSR = %x\r\n", stacked_psr);
  printf ("BFAR = %x\r\n", (*((volatile unsigned long *)(0xE000ED38))));
  printf ("CFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED28))));
  printf ("HFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED2C))));
  printf ("DFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED30))));
  printf ("AFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED3C))));
  printf ("SCB_SHCSR = %x\r\n", SCB->SHCSR);
 
  while (1);
#endif
}
#if 1
void __HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}
#endif
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */

void SVC_Handler(void) 
{
  vPortSVCHandler();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  xPortPendSVHandler();
}
extern void user_tick_hnd(void);
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) 
{
  xPortSysTickHandler();
  
}

/******************************************************************************/
/*                 STM32F2xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f2xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
 /*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
 ///// sdio_irq();
}
////extern void sdio_dma_irq(void);
void DMA2_Stream3_IRQHandler(void)
{
////sdio_dma_irq();
}
extern void usart1_tx_dma_irq(void);
void DMA2_Stream7_IRQHandler(void)
{ 
//// usart1_tx_dma_irq();
}
//// extern void usart1_rx_dma_irq(void);
void DMA2_Stream2_IRQHandler(void)
{ 
//// usart1_rx_dma_irq();
}
////=============================
#if 0
/*Bluretooth UART API */
void DMA2_Stream1_IRQHandler(void)
{ 
////  usart6_rx_dma_irq();
}

void DMA2_Stream6_IRQHandler(void)
{
 //// usart6_tx_dma_irq();
}

void USART6_IRQHandler(void)
{  
 ////   usart6_irq();
}
#endif
////=============================

/*EXTI ISR*/
void EXTI0_IRQHandler(void)
{
////gpio_irq();//SDIO OOB interrupt
}

void EXTI1_IRQHandler(void)
{
////    gpio_irq();
}

void EXTI2_IRQHandler(void)
{
 ////   gpio_irq();
}

void EXTI3_IRQHandler(void)
{
 ////   gpio_irq();//User defined external interrupt, EMW3162 button 1: PA3
}

void EXTI4_IRQHandler(void)
{
////    gpio_irq();
}

void EXTI9_5_IRQHandler(void)
{
////    gpio_irq(); //User defined external interrupt, EMW3161 button 1: PH9
}

void EXTI15_10_IRQHandler(void)
{
////    gpio_irq();
}

////============= CAN1 =================================================
///#include "can.h"
////extern __IO uint32_t ret;
extern uint8_t  CAN_TxRdy;              /* CAN HW ready to transmit message */
extern CanRxMsg RxMessage;
#if 0
void _CAN1_RX0_IRQHandler(void)
{
////  CanRxMsg RxMessage;
if (CAN1->RF0R & CAN_RF0R_FMP0)
  {			
  RxMessage.StdId = 0x00;
  RxMessage.ExtId = 0x00;
  RxMessage.IDE = 0;
  RxMessage.DLC = 0;
  RxMessage.FMI = 0;
  RxMessage.Data[0] = 0x00;
  RxMessage.Data[1] = 0x00;

  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  CAN_RxRdy=1;
  }
#if 0
  if((RxMessage.ExtId == 0x1234) && (RxMessage.IDE == CAN_ID_EXT)
     && (RxMessage.DLC == 2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8) == 0xDECA))
  {
    ret = 1; 
  }
  else
  {
    ret = 0; 
  }
#else


#endif
}
/*----------------------------------------------------------------------------
  CAN transmit interrupt handler
 *----------------------------------------------------------------------------*/
void _CAN1_TX_IRQHandler (void) 
{
if (CAN1->TSR & CAN_TSR_RQCP0)          /* request completed mbx 0        */
  {         
   CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */
   CAN1->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
  CAN_TxRdy = 1;
  }
}
#endif

///==================================================
#ifdef USEUSB

#include "usb_core.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
/////extern void my_USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
extern xQueueHandle q_usb_in;
////USB_OTG_CORE_HANDLE           *pUSB_OTG_dev;
/**
* @brief  This function handles OTG_HS Handler.
* @param  None
* @retval None
*/
void OTG_FS_IRQHandler(void)
{
USBD_OTG_ISR_Handler(&USB_OTG_dev) ; 
#if 0  
///signed portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
///pUSB_OTG_dev=&USB_OTG_dev;
////xQueueSendFromISR(q_usb_in, &pUSB_OTG_dev, &xHigherPriorityTaskWoken);
my_USBD_OTG_ISR_Handler (&USB_OTG_dev);
#endif  
}

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED 
/**
* @brief  This function handles EP1_IN Handler.
* @param  None
* @retval None
*/
void OTG_HS_EP1_IN_IRQHandler(void)
{
  USBD_OTG_EP1IN_ISR_Handler (&USB_OTG_dev);
}

/**
* @brief  This function handles EP1_OUT Handler.
* @param  None
* @retval None
*/
void OTG_HS_EP1_OUT_IRQHandler(void)
{
  USBD_OTG_EP1OUT_ISR_Handler (&USB_OTG_dev);
}
#endif  /// USEUSB
#endif