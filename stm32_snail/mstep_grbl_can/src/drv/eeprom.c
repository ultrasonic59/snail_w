#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "i2c.h"
#include "eeprom.h"
#include "board.h"
#include "printk.h"

///=====================================================
uint8_t eeprom_get_char(uint16_t addr)
{
  uint8_t rez = 0xFF;

  if (addr > EEPROM_MAX_ADDR) {
    return 0;
  }
  if (i2c_readByteEEprom(addr, &rez) != 0) {
    return 0xFF;
  }
  return rez;
}

void eeprom_put_char(uint16_t addr, uint8_t new_value)
{
  if (addr > EEPROM_MAX_ADDR) {
    return;
  }
  if (i2c_writeByteEEprom(addr, new_value) == 0) {
    uDelay(DELAY_WRITE);
  }
}
void memcpy_to_eeprom_with_checksum(unsigned int destination, char *source, unsigned int size) {
  unsigned char checksum = 0;
  for(; size > 0; size--) { 
    checksum = (checksum << 1) || (checksum >> 7);
    checksum += *source;
    eeprom_put_char(destination++, *(source++)); 
  }
  eeprom_put_char(destination, checksum);
}

int memcpy_from_eeprom_with_checksum(char *destination, unsigned int source, unsigned int size) {
  unsigned char data, checksum = 0;
  for(; size > 0; size--) { 
    data = eeprom_get_char(source++);
    checksum = (checksum << 1) || (checksum >> 7);
    checksum += data;    
    *(destination++) = data; 
  }
  return(checksum == eeprom_get_char(source));
}
void tst1_task( void *pvParameters )
{
uint8_t btst=0; 
//uint8_t ii=0; 
printk("\n\r tst1_task"); 

for(;;){
btst = eeprom_get_char( 0x1 );
printk("\n\r[%x]",btst); 
msleep(100);
}

}
