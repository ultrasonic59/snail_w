/*********************************************************************************************************
*
* File                : includes.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/


#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#define LED1_Port						GPIOH
#define LED1_Pin						GPIO_Pin_2
#define LED1_RCC_AHBPeriph				RCC_AHB1Periph_GPIOH

#define LED2_Port						GPIOH
#define LED2_Pin						GPIO_Pin_3
#define LED2_RCC_AHBPeriph				RCC_AHB1Periph_GPIOH

#define LED3_Port						GPIOI
#define LED3_Pin						GPIO_Pin_8
#define LED3_RCC_AHBPeriph				RCC_AHB1Periph_GPIOI

#define LED4_Port						GPIOI
#define LED4_Pin						GPIO_Pin_10
#define LED4_RCC_AHBPeriph				RCC_AHB1Periph_GPIOI

/* Includes ------------------------------------------------------------------*/
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

#include  <uCOS-II\Source\ucos_ii.h>
#include  <uCOS-II\Ports\ARM-Cortex-M3\RealView\os_cpu.h>
#include  <uC-CPU\ARM-Cortex-M3\RealView\cpu.h>
#include  <lib_def.h>
#include  <lib_mem.h>
#include  <lib_str.h>

#if (OS_VIEW_MODULE == DEF_ENABLED)
#include    <uCOS-VIEW\Ports\ARM-Cortex-M3\Realview\os_viewc.h>
#include    <uCOS-VIEW\Source\os_view.h>
#endif

#include    <GUI.h>
#include    <stm32f4xx.h>
#include    "TouchPanel.h"
#include    "LCDConf.h"
#include    "GLCD.h"

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


