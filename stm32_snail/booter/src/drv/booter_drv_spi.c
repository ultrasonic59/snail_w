
///#include "board_cnf.h"
#include "rook_v3_brd.h"
#include "drv_spi.h"
#include "fpga_mmap.h"
///====================================
void hw_spi1_set_br(u16 br)
{
uint16_t tmpreg = 0;
tmpreg = SPI1->CR1& ~(0x7<<3);
tmpreg |=	br&(0x7<<3);
SPI1->CR1=tmpreg;
}
void hw_spi1_set_data_size(u16 ds)
{
 uint16_t tmpreg = 0;
tmpreg = SPI1->CR1& ~(0x1<<11);
tmpreg |=	ds&(0x1<<11);
SPI1->CR1=tmpreg;
}
void hw_spi1_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;

/* Enable SPI1 Periph clock */
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA 
			| RCC_AHB1Periph_GPIOB
			| RCC_AHB1Periph_GPIOD,
                              ENABLE);

GPIO_PinAFConfig(SPI1_SCK_GPIO, SPI1_SCK_NPIN, GPIO_AF_SPI1);
GPIO_PinAFConfig(SPI1_MISO_GPIO, SPI1_MISO_NPIN, GPIO_AF_SPI1);
GPIO_PinAFConfig(SPI1_MOSI_GPIO, SPI1_MOSI_NPIN, GPIO_AF_SPI1);

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

 /* Configure SPI1 pins: PB3-SCK, PB4-MISO and PA7-MOSI */
GPIO_InitStructure.GPIO_Pin = SPI1_SCK_PIN;
GPIO_Init(SPI1_SCK_GPIO, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = SPI1_MISO_PIN;
GPIO_Init(SPI1_MISO_GPIO, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_PIN;
GPIO_Init(SPI1_MOSI_GPIO, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = SPI1_NSS_PIN;
GPIO_Init(SPI1_NSS_GPIO, &GPIO_InitStructure);
GPIO_SetBits(SPI1_NSS_GPIO, SPI1_NSS_PIN);
///=============spi1 addr dat pin =========================
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = SPI1_A_D_PIN;
GPIO_Init(SPI1_A_D_GPIO, &GPIO_InitStructure);
GPIO_ResetBits(SPI1_A_D_GPIO, SPI1_A_D_PIN);
///=============spi1 read write pin =========================
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = SPI1_R_W_PIN;
GPIO_Init(SPI1_R_W_GPIO, &GPIO_InitStructure);
GPIO_ResetBits(SPI1_R_W_GPIO, SPI1_R_W_PIN);
///=============spi1 SD pin =========================
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin   = SPI1_SD_PIN;
GPIO_Init(SPI1_SD_GPIO, &GPIO_InitStructure);
GPIO_ResetBits(SPI1_SD_GPIO, SPI1_SD_PIN);

SPI_I2S_DeInit(SPI1);
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;///SPI_NSS_Hard;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStructure.SPI_CRCPolynomial = 7;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
SPI_Init(SPI1, &SPI_InitStructure);
SPI_Cmd(SPI1, ENABLE);


#if 0
  /* Configure the SPI interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif


}
///=====================================
///=====================================
///=====================================
extern void spi_set_addr(uint16_t i_addr);
extern void spi_set_dat(uint16_t i_dat);
extern uint16_t spi_get_dat(void);
volatile uint32_t zzz;
///======================================
#if 0
void wr_dat_addr(u16 addr,u16 dat)
{
spi_set_addr(addr);
spi_set_dat(dat);
}
#endif
void wr_dat_addr32(u16 addr,u32 dat)
{
spi_set_addr(addr|INC_ADDR_FLG);
spi_set_dat(dat&0xffff);
spi_set_dat((dat>>16)&0xffff);
}

void wr_dat_blok(u16 addr,u16 len,u16 *ibuf)
{
u16 ii;
spi_set_addr(addr|INC_ADDR_FLG);
for(ii=0;ii<len;ii++)
	{
        spi_set_dat(*(ibuf+ii));
	}
}
#if 0
u16 rd_dat_addr(u16 addr)
{
u16 rez;
spi_set_addr(addr);
rez= spi_get_dat();
return rez;
}
#endif
u32 rd_dat_addr32(u16 addr)
{
u32 rez;
u16 tmp;
spi_set_addr(addr|INC_ADDR_FLG);
tmp= spi_get_dat();
rez= spi_get_dat();
rez<<=16;
rez|=tmp;
return rez;
}

void rd_dat_blok(u16 addr,u16 len,u16 *obuf)
{
u16 ii;
u16 t_dat;
spi_set_addr(addr|INC_ADDR_FLG);
for(ii=0;ii<len;ii++)
	{
	t_dat=spi_get_dat();
	*(obuf+ii)=t_dat;
	}
}



