#include <stdlib.h>
#include <string.h>

#include "rook_v4e.h"
#include "rook_v3_brd.h"
#include "drv_spi.h"
#include "fpga_mmap.h"
#include "rook_sdc.h"
#include "common.h"

///====================================
#define MIN_FR_CLK_DIV  50
#define MAX_FR_CLK_DIV  2

extern void wr_dat_addr_m(u16 addr,u16 dat);

mmc_t cur_mmc;
///=========================================
#define  UNSTUFF_BITS  unstuff_bits    
///===========================================
u32 unstuff_bits(u32 *resp, u32 start, u32 size)
{
    const u32 __mask = (1 << (size)) - 1;
    const int __off = 3 - ((start) / 32);
    const int __shft = (start) & 31;
    u32 __res;

    __res = resp[__off] >> __shft;
    if ((size) + __shft >= 32)
        __res |= resp[__off-1] << (32 - __shft);
    return __res & __mask;
}
///===========================================

static const int fbase[] = {
	10000,
	100000,
	1000000,
	10000000,
        0,0,0,0
};
/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
static const int multipliers[] = {
	0,	/* reserved */
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80,
};
static const unsigned int tran_exp[] = {
	10000,		100000,		1000000,	10000000,
	0,		0,		0,		0
};

static const unsigned char tran_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

static const unsigned int tacc_exp[] = {
	1,	10,	100,	1000,	10000,	100000,	1000000, 10000000,
};

static const unsigned int tacc_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

///static int mmc_go_idle(mmc_t* mmc);
///static int mmc_send_if_cond(mmc_t *mmc);
///===========================================
///static inline 
uint16_t sdc_read16(mmc_t *dev, int offset)
{
return rd_dat_addr(dev->iobase + offset);
}

///static inline 
void sdc_read_blok(mmc_t *dev, int offset,int len,uint16_t *obuf)
{
rd_dat_blok(dev->iobase + offset,len,obuf);
}

///static inline 
uint32_t sdc_read32(mmc_t *dev, int offset)
{
return rd_dat_addr32(dev->iobase + offset);
}

////static inline 
void sdc_write32(mmc_t *dev, int offset, uint32_t data)
{
wr_dat_addr32(dev->iobase + offset,data);  
}
///static inline 
void sdc_write16(mmc_t *dev, int offset, uint16_t data)
{
 wr_dat_addr(dev->iobase + offset,data);  
}
////static inline 
void sdc_write_blok(mmc_t *dev, int offset,int len,uint16_t *ibuf)
{
wr_dat_blok(dev->iobase + offset,len,ibuf);  
}

u8 check_sd_inst(void)
{
u16 tmp;
tmp=SD_INST_GPIO->IDR;
///tmp= rd_dat_addr(ADDR_SPI_RDY);
///=========================
////printk(" sd_inst =%x\n",tmp);
///=========================
#if SD_INST_VSS	
///if(tmp & BIT_SD_INST)
if(tmp & (0x1<<SD_INST_NPIN))
	return FALSE;
else
	return TRUE;
#elif SD_INST_VDD
if(tmp & (0x1<<SD_INST_NPIN))
	return TRUE;
else
	return FALSE;
#else
#error SD_INST XXX
#endif
}

///========================================
#define ADDR_ON_VDD_SD	0x20

void on_pow_sd(uint8_t on_off)
{
  wr_dat_addr(ADDR_ON_VDD_SD,on_off&0x1);
}
#if 1
/* Set clock prescalar value based on the required clock in HZ */
static void sdc_set_clock(mmc_t* dev, uint clock)
{

///int clk_div = (int)(dev->clk_freq / (2.0 * clock) - 1);
int clk_div = (int)(dev->clk_freq / (int)(2 * clock) - 1);

////_printk("\n\r sdc_set_clock %d, div %d[%d]\n\r", clock, clk_div,dev->clk_freq);
//software reset
sdc_write16(dev, OCSDC_SOFTWARE_RESET, 1);
//set clock devider
sdc_write16(dev, OCSDC_CLOCK_DIVIDER, clk_div);
//clear software reset
sdc_write16(dev, OCSDC_SOFTWARE_RESET, 0);
}
#endif
////static 
void sdc_set_buswidth(mmc_t* dev, uint width) 
{
if (width == 4)
  sdc_write16(dev, OCSDC_CONTROL, 1);
else ///if (width == 1)
  sdc_write16(dev, OCSDC_CONTROL, 0);
}
////static 
void mmc_set_clock(mmc_t *mmc, uint clock)
{
if (clock > mmc->f_max)
  clock = mmc->f_max;
if (clock < mmc->f_min)
  clock = mmc->f_min;
///return ;  
mmc->clock = clock;
sdc_set_clock(mmc,clock);
}

////static 
int sdc_finish(mmc_t* dev, struct mmc_cmd *cmd) 
{
int retval = 0;
///return 0;

while (1) 
  {
  int r2 = sdc_read16(dev, OCSDC_CMD_INT_STATUS);
  //printf("ocsdc_finish: cmd %d, status %x\n", cmd->cmdidx, r2);
  if (r2 & OCSDC_CMD_INT_STATUS_EI) 
    {
    //clear interrupts
    sdc_write16(dev, OCSDC_CMD_INT_STATUS, 0);
////    _printk("ocsdc_finish: cmd %d, status %x\n\r", cmd->cmdidx, r2);
    retval = -1;
    break;
    }
  else if (r2 & OCSDC_CMD_INT_STATUS_CC) 
    {
  //clear interrupts
  sdc_write16(dev, OCSDC_CMD_INT_STATUS, 0);
  //get response
  cmd->response[0] = sdc_read32(dev, OCSDC_RESPONSE_1);
  if (cmd->resp_type & MMC_RSP_136) 
    {
    cmd->response[1] = sdc_read32(dev, OCSDC_RESPONSE_2);
    cmd->response[2] = sdc_read32(dev, OCSDC_RESPONSE_3);
    cmd->response[3] = sdc_read32(dev, OCSDC_RESPONSE_4);
    }
 //// _printk("sdc_finish:  %d ok\n\r", cmd->cmdidx);
  retval = 0;
  break;
  }
}
return retval;
}

int mmc_send_cmd(mmc_t *dev, struct mmc_cmd *cmd, struct mmc_data *data)
{
int rez=0;  
int status;
int command = (cmd->cmdidx << 8);
if (cmd->resp_type & MMC_RSP_PRESENT) 
  {
  if (cmd->resp_type & MMC_RSP_136)
    command |= 2;
  else 
    command |= 1;
  }
if (cmd->resp_type & MMC_RSP_BUSY)
  command |= (1 << 2);
if (cmd->resp_type & MMC_RSP_CRC)
  command |= (1 << 3);
if (cmd->resp_type & MMC_RSP_OPCODE)
  command |= (1 << 4);

if (data && ((data->flags & MMC_DATA_READ) || ((data->flags & MMC_DATA_WRITE))) && data->blocks) 
  {
  if (data->flags & MMC_DATA_READ)
    command |= (1 << 5);
  else if (data->flags & MMC_DATA_WRITE)
    {
    uint16_t *tbuf=(uint16_t *)data->dest;
    command |= (1 << 6);
    sdc_write_blok(dev,OCSDC_RAM_ADDR,256,tbuf);
    }
  sdc_write16(dev, OCSDC_BLOCK_SIZE, data->blocksize);
  }

sdc_write16(dev, OCSDC_COMMAND, command);
sdc_write32(dev, OCSDC_ARGUMENT, cmd->cmdarg);
if (sdc_finish(dev, cmd) < 0) 
   return -1;
        
if (data && data->blocks) 
    {
    while ((status = sdc_read16(dev, OCSDC_DAT_INT_STATUS)) == 0);
    sdc_write16(dev, OCSDC_DAT_INT_STATUS, 0);        ///clr status dat irq
    if (status & SDC_DAT_INT_STATUS_EI) ///error
       {
       _printk("\n\r err sdc_data_finish : status %x\n\r", status);
       rez= -1;
       }
    else
      {
      rez=0;
      if (data->flags & MMC_DATA_READ)
        {
        uint16_t *tbuf=(uint16_t *)data->src;
        sdc_read_blok(dev,OCSDC_RAM_ADDR,256,tbuf);
        }
      }
    }
return rez;
}
///=======================================================
////static 
int mmc_go_idle(mmc_t* mmc)
{
struct mmc_cmd cmd;
int err;

uDelay(1000);
cmd.cmdidx = MMC_CMD_GO_IDLE_STATE;
cmd.cmdarg = 0;
cmd.resp_type = MMC_RSP_NONE;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
uDelay(2000);
return 0;
}
///============= cmd8 =============================
static int mmc_send_if_cond(mmc_t *mmc)
{
struct mmc_cmd cmd;
int err;
cmd.cmdidx = SD_CMD_SEND_IF_COND;
/* We set the bit if the host supports voltages between 2.7 and 3.6 V */
cmd.cmdarg = ((mmc->voltages & 0xff8000) != 0) << 8 | 0xaa;
cmd.resp_type = MMC_RSP_R7;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
if ((cmd.response[0] & 0xff) != 0xaa)
  return UNUSABLE_ERR;
else
  mmc->version = SD_VERSION_2;
return 0;
}
///==============================================
static int sd_send_op_cond(mmc_t *mmc)
{
int timeout = 1000;
int err;
struct mmc_cmd cmd;

do {
    cmd.cmdidx = MMC_CMD_APP_CMD;
    cmd.resp_type = MMC_RSP_R1;
    cmd.cmdarg = 0;
    err = mmc_send_cmd(mmc, &cmd, NULL);
    if (err)
      return err;
    cmd.cmdidx = SD_CMD_APP_SEND_OP_COND;
    cmd.resp_type = MMC_RSP_R3;
    cmd.cmdarg = (mmc->voltages & 0xff8000);
  if (mmc->version == SD_VERSION_2)
    cmd.cmdarg |= OCR_HCS;
  err = mmc_send_cmd(mmc, &cmd, NULL);
  if (err)
    return err;
  uDelay(1000);
    } while ((!(cmd.response[0] & OCR_BUSY)) && timeout--);
  if (timeout <= 0)
    return TIMEOUT;
  if (mmc->version != SD_VERSION_2)
    mmc->version = SD_VERSION_1_0;
  mmc->ocr = cmd.response[0];
  mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
  if(mmc->high_capacity)
    mmc->card_type=MMC_CARDTYPE_SDHC;
  else
    mmc->card_type=MMC_CARDTYPE_SD;
 mmc->rca = 0;
return 0;
}
///============================================
static int mmc_send_op_cond(mmc_t *mmc)
{
///int timeout = 10000;
int timeout = 100;
struct mmc_cmd cmd;
int err;
/* Some cards seem to need this */
///mmc_go_idle(mmc);

/* Asking to the card its capabilities */
cmd.cmdidx = MMC_CMD_SEND_OP_COND;
cmd.resp_type = MMC_RSP_R3;
cmd.cmdarg = 0;

err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
uDelay(1000);
do {
  cmd.cmdidx = MMC_CMD_SEND_OP_COND;
  cmd.resp_type = MMC_RSP_R3;
  cmd.cmdarg =
    (mmc->voltages &
    (cmd.response[0] & OCR_VOLTAGE_MASK)) |
    (cmd.response[0] & OCR_ACCESS_MODE);
  if (mmc->host_caps & MMC_MODE_HC)
    cmd.cmdarg |= OCR_HCS;
  err = mmc_send_cmd(mmc, &cmd, NULL);
  if (err)
    return err;
  uDelay(1000);
  } while (!(cmd.response[0] & OCR_BUSY) && timeout--);
if (timeout <= 0)
  return UNUSABLE_ERR;
mmc->version = MMC_VERSION_UNKNOWN;
mmc->ocr = cmd.response[0];
mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
mmc->rca = 0;
return 0;
}
///================================================
static int mmc_get_cid(mmc_t *mmc)
{
int err=0;
struct mmc_cmd cmd;
/* Put the Card in Identify Mode */
cmd.cmdidx = MMC_CMD_ALL_SEND_CID; ///CMD2 /* cmd not supported in spi */
cmd.resp_type = MMC_RSP_R2;
cmd.cmdarg = 0;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
memcpy(mmc->cid, cmd.response, 16);
return 0;
}
static int mmc_send_status(mmc_t *mmc, int timeout)
{
struct mmc_cmd cmd;
int err, retries = 5;

cmd.cmdidx = MMC_CMD_SEND_STATUS;
cmd.resp_type = MMC_RSP_R1;
cmd.cmdarg = mmc->rca << 16;

do {
  err = mmc_send_cmd(mmc, &cmd, NULL);
  if (!err) {
  if ((cmd.response[0] & MMC_STATUS_RDY_FOR_DATA) &&
      (cmd.response[0] & MMC_STATUS_CURR_STATE) !=
      MMC_STATE_PRG)
      break;
  else if (cmd.response[0] & MMC_STATUS_MASK) {
////				_printk("Status Error: 0x%08X\n\r",
///      cmd.response[0]);
      return COMM_ERR;
      }
    } else if (--retries < 0)
  return err;
  uDelay(1000);
} while (timeout--);
if (timeout <= 0) {
///		_printk("Timeout waiting card ready\n\r");
  return TIMEOUT;
  }
return 0;
}
/*
 * Given a 128-bit response, decode to our card CSD structure.
 */
static int mmc_decode_csd(mmc_t *mmc)
{
mmc_csd_t *csd = &mmc->csd;
///unsigned int a, b;
unsigned int e, m, csd_struct;
u32 *resp = &mmc->csd_raw[0];

	csd_struct = UNSTUFF_BITS(resp, 126, 2);

	switch (csd_struct) {
	case 0:
		m = UNSTUFF_BITS(resp, 115, 4);
		e = UNSTUFF_BITS(resp, 112, 3);
		csd->tacc_ns	 = (tacc_exp[e] * tacc_mant[m] + 9) / 10;
		csd->tacc_clks	 = UNSTUFF_BITS(resp, 104, 8) * 100;

		m = UNSTUFF_BITS(resp, 99, 4);
		e = UNSTUFF_BITS(resp, 96, 3);
		csd->max_dtr	  = tran_exp[e] * tran_mant[m];
		csd->cmdclass	  = UNSTUFF_BITS(resp, 84, 12);

		e = UNSTUFF_BITS(resp, 47, 3);
		m = UNSTUFF_BITS(resp, 62, 12);
		csd->capacity	  = (1 + m) << (e + 2);

		csd->read_blkbits = UNSTUFF_BITS(resp, 80, 4);
		csd->read_partial = UNSTUFF_BITS(resp, 79, 1);
		csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
		csd->read_misalign = UNSTUFF_BITS(resp, 77, 1);
		csd->dsr_imp = UNSTUFF_BITS(resp, 76, 1);
		csd->r2w_factor = UNSTUFF_BITS(resp, 26, 3);
		csd->write_blkbits = UNSTUFF_BITS(resp, 22, 4);
		csd->write_partial = UNSTUFF_BITS(resp, 21, 1);

		if (UNSTUFF_BITS(resp, 46, 1)) {
			csd->erase_size = 1;
		} else if (csd->write_blkbits >= 9) {
			csd->erase_size = UNSTUFF_BITS(resp, 39, 7) + 1;
			csd->erase_size <<= csd->write_blkbits - 9;
		}
		break;
	case 1:
		/*
		 * This is a block-addressed SDHC or SDXC card. Most
		 * interesting fields are unused and have fixed
		 * values. To avoid getting tripped by buggy cards,
		 * we assume those fixed values ourselves.
		 */
		mmc_card_set_blockaddr(mmc);

		csd->tacc_ns	 = 0; /* Unused */
		csd->tacc_clks	 = 0; /* Unused */

		m = UNSTUFF_BITS(resp, 99, 4);
		e = UNSTUFF_BITS(resp, 96, 3);
		csd->max_dtr	  = tran_exp[e] * tran_mant[m];
		csd->cmdclass	  = UNSTUFF_BITS(resp, 84, 12);
		csd->c_size	  = UNSTUFF_BITS(resp, 48, 22);

		/* SDXC cards have a minimum C_SIZE of 0x00FFFF */
		if (csd->c_size >= 0xFFFF)
			mmc_card_set_ext_capacity(mmc);

		m = UNSTUFF_BITS(resp, 48, 22);
////		csd->capacity     = (1 + m) << 10;
		csd->capacity     = (1 + m) *512;

		csd->read_blkbits = 9;
		csd->read_partial = 0;
		csd->write_misalign = 0;
		csd->read_misalign = 0;
		csd->r2w_factor = 4; /* Unused */
		csd->write_blkbits = 9;
		csd->write_partial = 0;
		csd->erase_size = 1;
		break;
	default:
////		_printk("\r\n unrecognised CSD structure version %d\n",
////			 csd_struct);
		return -1;
	}

	mmc->erase_size = csd->erase_size;

	return 0;
}

static int mmc_get_rca(mmc_t *mmc)
{
int err=0;
struct mmc_cmd cmd;
cmd.cmdidx = SD_CMD_SEND_RELATIVE_ADDR; ///CMD3
cmd.cmdarg = mmc->rca << 16;
cmd.resp_type = MMC_RSP_R6;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
if (IS_SD(mmc))
  mmc->rca = (cmd.response[0] >> 16) & 0xffff;
return 0;
}
static int mmc_get_csd(mmc_t *mmc)
{
int err=0;
struct mmc_cmd cmd;
int timeout = 1000;
	uint mult, freq;
	uint cmult, csize;
cmd.cmdidx = MMC_CMD_SEND_CSD;          ///CMD9
cmd.resp_type = MMC_RSP_R2;
cmd.cmdarg = mmc->rca << 16;
err = mmc_send_cmd(mmc, &cmd, NULL);
/* Waiting for the ready status */
mmc_send_status(mmc, timeout);

if (err)
  return err;
mmc->csd_raw[0] = cmd.response[0];
mmc->csd_raw[1] = cmd.response[1];
mmc->csd_raw[2] = cmd.response[2];
mmc->csd_raw[3] = cmd.response[3];
mmc_decode_csd(mmc);  
if (mmc->version == MMC_VERSION_UNKNOWN) 
  {
  int version = (cmd.response[0] >> 26) & 0xf;
  switch (version) 
    {
    case 0:
      mmc->version = MMC_VERSION_1_2;
      break;
    case 1:
      mmc->version = MMC_VERSION_1_4;
      break;
    case 2:
      mmc->version = MMC_VERSION_2_2;
      break;
    case 3:
      mmc->version = MMC_VERSION_3;
      break;
    case 4:
      mmc->version = MMC_VERSION_4;
      break;
    default:
      mmc->version = MMC_VERSION_1_2;
      break;
      }
  }
/* divide frequency by 10, since the mults are 10x bigger */
freq = fbase[(cmd.response[0] & 0x7)];
mult = multipliers[((cmd.response[0] >> 3) & 0xf)];
mmc->tran_speed = freq * mult;
mmc->read_bl_len = 1 << ((cmd.response[1] >> 16) & 0xf);
///=========================================        
if (IS_SD(mmc))
  mmc->write_bl_len = mmc->read_bl_len;
else
  mmc->write_bl_len = 1 << ((cmd.response[3] >> 22) & 0xf);

	if (mmc->high_capacity) {
		csize = (mmc->csd_raw[1] & 0x3f) << 16
			| (mmc->csd_raw[2] & 0xffff0000) >> 16;
		cmult = 8;
	} else {
		csize = (mmc->csd_raw[1] & 0x3ff) << 2
			| (mmc->csd_raw[2] & 0xc0000000) >> 30;
		cmult = (mmc->csd_raw[2] & 0x00038000) >> 15;
	}

	mmc->capacity = (csize + 1) << (cmult + 2);
	mmc->capacity *= mmc->read_bl_len;

	if (mmc->read_bl_len > 512)
		mmc->read_bl_len = 512;

	if (mmc->write_bl_len > 512)
		mmc->write_bl_len = 512;

return 0;
}
static int mmc_sel_desel(mmc_t *mmc,int sel_desel)
{
int err=0;
struct mmc_cmd cmd;
/* Select the card, and put it into Transfer Mode */
cmd.cmdidx = MMC_CMD_SELECT_CARD;       ///CMD7
cmd.resp_type = MMC_RSP_R1;
if(sel_desel)
  cmd.cmdarg = mmc->rca << 16;
else
  cmd.cmdarg = 0;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
return 0;
}
static int mmc_set_bus_width(mmc_t *mmc,int width)
{
int err=0;
struct mmc_cmd cmd;
cmd.cmdidx = MMC_CMD_APP_CMD;
cmd.resp_type = MMC_RSP_R1;
cmd.cmdarg = mmc->rca << 16;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;

cmd.cmdidx = SD_CMD_APP_SET_BUS_WIDTH;
cmd.resp_type = MMC_RSP_R1;
if(width==4)
  cmd.cmdarg = 0x1<<1;
else
  cmd.cmdarg = 0;
err = mmc_send_cmd(mmc, &cmd, NULL);
if (err)
  return err;
mmc->bus_width = width;
sdc_set_buswidth(mmc,mmc->bus_width); 
return 0;
}
///========================================================
static int mmc_set_blocklen(mmc_t *mmc, int len)
{
struct mmc_cmd cmd;

cmd.cmdidx = MMC_CMD_SET_BLOCKLEN;
cmd.resp_type = MMC_RSP_R1;
cmd.cmdarg = len;

return mmc_send_cmd(mmc, &cmd, NULL);
}

///========================================================
int sdc_mmc_init(mmc_t *mmc,int base_addr, int clk_freq)
{
int err;
///printf("\n\r sdc_mmc_init");

if (mmc->has_init)
  return 0;
memset(mmc, 0, sizeof(mmc_t));

mmc->iobase = base_addr;
mmc->clk_freq = clk_freq;
mmc->f_min = MIN_MMC_CLK;///mmc->clk_freq/6; /*maximum clock division 64 */
mmc->f_max = mmc->clk_freq/2; /*minimum clock division 2 */
mmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;
mmc->host_caps = MMC_MODE_4BIT;//MMC_MODE_HS | MMC_MODE_HS_52MHz | MMC_MODE_4BIT;
mmc->b_max = 256;
/* Initialize sdc controller */
//set timeout
sdc_write32(mmc, OCSDC_TIMEOUT, 0x7FFF);
//disable all interrupts
sdc_write16(mmc, OCSDC_CMD_INT_ENABLE, 0);
sdc_write16(mmc, OCSDC_DAT_INT_ENABLE, 0);
//clear all interrupts
sdc_write16(mmc, OCSDC_CMD_INT_STATUS, 0);
sdc_write16(mmc, OCSDC_DAT_INT_STATUS, 0);
sdc_set_clock(mmc, mmc->f_min);
////sdc_set_clock_div(mmc, MIN_FR_CLK_DIV);
/* Reset the Card */
err = mmc_go_idle(mmc);
if (err)
  return err;
mmc->part_num = 0;
/* Test for SD version 2 */
err = mmc_send_if_cond(mmc); ///CMD8
err = sd_send_op_cond(mmc);
if (err != 0)
    {
    err = mmc_send_op_cond(mmc);///CMD1
    if(err==0)
      {
      mmc->card_type=MMC_CARDTYPE_MMC;
      }
    else
      {
      mmc->card_type=MMC_CARDTYPE_NONE;
////      printk("Card did not respond to voltage select!\n\r");
      return err;
      }
    }

err = mmc_get_cid(mmc);         ///CMD2
if (err)
  return err;
err = mmc_get_rca(mmc);         ///CMD3
if (err)
  return err;
err = mmc_get_csd(mmc);         ///CMD9
if (err)
  return err;
//
///================================
err = mmc_sel_desel(mmc,1);         ///CMD7 sel
if (err)
  return err;
#if 1
err = mmc_set_bus_width(mmc,4);         ///ACMD6
if (err)
  return err;
#endif
 mmc_set_clock(mmc, mmc->tran_speed);
///==========================================
err =mmc_set_blocklen(mmc, mmc->read_bl_len);
if (err)
  return err;

///=================================
///err = mmc_startup(mmc);
///#endif
if (err)
  mmc->has_init = 0;
else
  mmc->has_init = 1;
return err;
}

int SD_Init (void)
{
int ret = TRUE;
int err;
mmc_t *drv=&cur_mmc; 
//init ocsdc driver
///on_pow_sd(0);
///uDelay(10000);  
  on_pow_sd(1);
uDelay(10000);  
drv->has_init = 0;
err = sdc_mmc_init(drv,ADDR_SDC, 40000000);
///======================================
 if (err != 0 || drv->has_init == 0) 
  {
  ret = FALSE;  
  }
///_printk("mmc_init success\n\r");

return ret;
}

///=======================================================
static int mmc_read_one_blok(mmc_t *mmc, uint8_t *dst, size_t start)
{
int err;  
struct mmc_cmd cmd;
struct mmc_data data;
  cmd.cmdidx = MMC_CMD_READ_SINGLE_BLOCK;
if (mmc->high_capacity)
  cmd.cmdarg = start;
else
  cmd.cmdarg = start * mmc->read_bl_len;
cmd.resp_type = MMC_RSP_R1;
data.dest = dst;
data.blocks = 1;
data.blocksize = mmc->read_bl_len;
data.flags = MMC_DATA_READ;
err=mmc_send_cmd(mmc, &cmd, &data);
  return err;
}

int SD_ReadSector(uint32_t sector, uint8_t *buff, uint32_t count)
{
#if 1
uint32_t ii;
int err;
uint32_t offs=0;
///mmc_sel_desel(&cur_mmc,1);      ///select
for(ii=0;ii<count;ii++)
  {
  err= mmc_read_one_blok(&cur_mmc, buff+offs,sector+ii);
  offs+= cur_mmc.read_bl_len;
  if(err)
    break;
  }
///mmc_sel_desel(&cur_mmc,0);      ///deselect
if(err)
  return FALSE;
else
#endif
  return TRUE;
}
static int mmc_write_one_blok(mmc_t *mmc, const uint8_t *dst, size_t start)
{
int err;  
struct mmc_cmd cmd;
struct mmc_data data;
  cmd.cmdidx = MMC_CMD_WRITE_SINGLE_BLOCK;
if (mmc->high_capacity)
  cmd.cmdarg = start;
else
  cmd.cmdarg = start * mmc->write_bl_len;
cmd.resp_type = MMC_RSP_R1;
data.dest = (uint8_t *)dst;
data.blocks = 1;
data.blocksize = mmc->write_bl_len;
data.flags = MMC_DATA_WRITE;
err=mmc_send_cmd(mmc, &cmd, &data);
  return err;
}

int SD_WriteSector(uint32_t sector, const uint8_t *buff, uint32_t count)
{
#if 1  
uint32_t ii;
int err;
uint32_t offs=0;
///mmc_sel_desel(&cur_mmc,1);      ///select
for(ii=0;ii<count;ii++)
  {
  err= mmc_write_one_blok(&cur_mmc, buff+offs,sector+ii);
  offs+= cur_mmc.write_bl_len;
  if(err)
    break;
  }
///mmc_sel_desel(&cur_mmc,0);      ///deselect
if(err)
  return FALSE;
else
#endif
  return TRUE;
}
