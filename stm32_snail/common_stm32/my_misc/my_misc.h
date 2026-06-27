#ifndef __MY_MISC_H__
#define __MY_MISC_H__
#include <stdint.h>
#include "can_cmds.h"

typedef  void (*pFunction)(void);
#define MIN_SIZE_APP 1024
///=======================================================================
extern void uDelay (const uint32_t usec);
extern void goto_booter(void);
extern void goto_app(void);
extern uint8_t erase_sectors(uint8_t *data);
extern uint8_t prg_dat(uint8_t *data);
extern void set_curr_addr_prg(uint32_t *iaddr);
extern uint8_t rd_nflash(prg_flash_cmd_t *data);

#endif ////  __MY_MISC_H__
