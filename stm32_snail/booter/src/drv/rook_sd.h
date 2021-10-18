#ifndef _ROOK_SD_H_
#define _ROOK_SD_H_
#include <stdint.h>
///============================
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define SD_SECTOR_SIZE  512
/* token for write operation */
#define TOKEN_SINGLE_BLOCK  0xFE
#define TOKEN_MULTI_BLOCK   0xFC
#define TOKEN_STOP_TRAN     0xFD
///============================
/* MMC/SD command (in SPI) */
#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
#define CMD1    (0x40+1)    /* SEND_OP_COND */
#define CMD8    (0x40+8)    
#define CMD9    (0x40+9)    /* SEND_CSD */
#define CMD10   (0x40+10)   /* SEND_CID */
#define CMD12   (0x40+12)   /* STOP_TRANSMISSION */
#define CMD13   (0x40+13)   
#define CMD16   (0x40+16)   
#define CMD17   (0x40+17)   /* READ_SINGLE_BLOCK */
#define CMD18   (0x40+18)   /* READ_MULTIPLE_BLOCK */
#define CMD24   (0x40+24)   /* WRITE_BLOCK */
#define CMD25   (0x40+25)   /* WRITE_MULTIPLE_BLOCK */
#define CMD55   (0x40+55)    /* APP_CMD */
#define CMD58   (0x40+58)   /* READ_OCR */
#define SEND_CSD  CMD9   		/* CMD9  R1  */
#define SEND_CID  CMD10  		/* CMD10 R1  */
#define STOP_TRAN        		CMD12
#define READ_BLOCK       		CMD17
#define READ_MULT_BLOCK  		CMD18

////#define SD_STATUS  CMD13   	/* ACMD13 R2 */
#define READ_OCR  CMD58  		/* CMD58 R3  */
#define GO_IDLE_STATE           CMD0
#define SEND_OP_COND            CMD1
#define SET_BLOCKLEN           	CMD16     // CMD16
#define WRITE_BLOCK							CMD24 					/* WRITE_BLOCK */
#define WRITE_MULT_BLOCK				CMD25 					/* WRITE_MULTIPLE_BLOCK */

#define APP_CMD 								CMD55   

#define SD_SEND_OP_COND         (0xC0 + 41)     // ACMD41
#define SD_STATUS               (0xC0 + 13)     // ACMD13, SD_STATUS (SDC)
#define SET_WR_BLK_ERASE_COUNT  (0xC0 + 23)     // ACMD23 (SDC)

#define SELECT()        	sd_select()
#define DESELECT()     	sd_deselect()
#define BIT_CS			(0x1<<0)
#define BIT_BUSY		(0x1<<1)
#define BIT_SD_INST		(0x1<<2)

/* Card type flags (CardType) */
#define CT_NONE             0x00
#define CT_MMC              0x01
#define CT_SD1              0x02
#define CT_SD2              0x04
#define CT_SDC              (CT_SD1|CT_SD2)
#define CT_BLOCK            0x08

typedef struct tagSDCFG
{
    uint32_t sernum;        // serial number
    uint32_t size;          // size=sectorsize*sectorcnt
    uint32_t sectorcnt;     //
    uint32_t sectorsize;    // 512
    uint32_t blocksize;     // erase block size
    uint8_t ocr[4];         // OCR
    uint8_t cid[16];        // CID
    uint8_t csd[16];        // CSD
} SDCFG;
///==========================================
extern int SD_Init(void);
extern uint8_t check_sd_inst(void);
extern void on_pow_sd(uint8_t on_off);
extern int SD_ReadSector(uint32_t sector, uint8_t *buff, uint32_t count);
extern int SD_WriteSector(uint32_t sector, const uint8_t *buff, uint32_t count);

///==========================================

#endif 
