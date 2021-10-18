#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include <stdint.h>
///#include "stm32f2xx.h"
#ifdef EMW3165
#include "stm32f4xx.h"
#else
#include "stm32f2xx.h"
#endif

///========================================
////#define SPI_USE_DMA
#undef SPI_USE_DMA
///============================================
extern void hw_spi1_set_br(u16 br);
extern void hw_spi1_set_data_size(u16 ds);
extern void hw_spi1_init(void);

///============================================


#endif // STM32F20X_40X_SPI_H_INCLUDED
