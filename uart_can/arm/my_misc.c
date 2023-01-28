#include <stdint.h>
uint8_t halfbyte_to_hexascii(uint8_t _halfbyte)
{
_halfbyte &= 0x0F;
if(_halfbyte >= 10) return('A' + _halfbyte - 10);
else return('0' + _halfbyte);
}

uint8_t hexascii_to_halfbyte(uint8_t _ascii)
{
if((_ascii >= '0') && (_ascii <= '9')) 
  return(_ascii - '0');
if((_ascii >= 'a') && (_ascii <= 'f')) 
  return(_ascii - 'a');
if((_ascii >= 'A') && (_ascii <= 'F')) 
  return(_ascii - 'A');
return(0xFF);
}

void bin2hex(uint8_t *dst, unsigned char c) {
    uint8_t nibble;

    nibble = ((c & 0xf0) >> 4) + '0';
    if (nibble >= 0x3a)
	nibble += 7;
    *dst++ = nibble;

    nibble = (c & 0x0f) + '0';
    if (nibble >= 0x3a)
	nibble += 7;
    *dst = nibble;
}

uint8_t nibble2bin(uint8_t s) {

    if (s >= '0' && s <= '9')
	return s - '0';
    if (s >= 'A' && s <= 'F')
	return s - 'A' + 10;
    return s - 'a' + 10;
}

uint8_t hex2bin(char *s) {
    uint8_t x;

    x = nibble2bin(*s++) << 4;
    x |= nibble2bin(*s);
    return x;
}
