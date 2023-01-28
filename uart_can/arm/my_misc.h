#ifndef _MY_MISC_H__
#define _MY_MISC_H__
#include <stdint.h>

extern void bin2hex(uint8_t *dst, unsigned char c);

extern uint8_t nibble2bin(uint8_t s);
extern uint8_t hex2bin(char *s);
extern uint8_t halfbyte_to_hexascii(uint8_t _halfbyte);

#endif ////_MY_MISC_H__