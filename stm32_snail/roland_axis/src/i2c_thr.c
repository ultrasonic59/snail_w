#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
///#include "stm32f2xx_gpio.h"
///#include "stm32f2xx_rcc.h"

#include "board.h"
#include "printk.h"
#include "oled.h"
#include "bitmap.h"
#include "horse_anim.h"

#if 0
uint32_t I2C_WrData(uint8_t DevAddr, uint8_t RegAddr, uint8_t data){
  //Write a single byte data to the given register address
  
  //Generate a Start condition
  I2C_Start();
  
  //Send I2C device Address and clear ADDR
  I2C_Addr(DevAddr, I2C_Direction_Transmitter);
  (void) I2Cx->SR2;
  
  //Send Data
  I2Cx->DR = data;
  WaitSR1FlagsSet(I2C_SR1_BTF);  //wait till the data is actually written.
  
  //Generate Stop
  I2Cx->CR1 |= I2C_CR1_STOP;
  
  //Wait to be sure that line is iddle
  WaitLineIdle();
  
  return 0;
}
#endif
///===========================================
void i2c_thr( void *pvParameters )
{
///  uint8_t ii=0;
printk("\n\r i2c_thr"); 
I2C_LowLevel_Init();
///SSD1306_Init();
 for(;;)
  {
    i2c_writeByte(0x4,0x5,0x35);
 /// SSD1306_GotoXY (0,0);
 /// SSD1306_Puts ("Embedded", &Font_7x10, 1);
  msleep(10);
  }
SSD1306_GotoXY (0, 10);
SSD1306_Puts ("Expret.io", &Font_7x10, 1);
SSD1306_GotoXY (0, 30);
SSD1306_Puts ("OLED Display", &Font_7x10, 1);
SSD1306_GotoXY (0, 50);
SSD1306_Puts ("Bare Metal Code", &Font_7x10, 1);
SSD1306_UpdateScreen(); //display
msleep(2000);
SSD1306_ScrollRight(0,7);  // scroll entire screen
msleep(2000);
SSD1306_ScrollLeft(0,7);  // scroll entire screen
msleep(2000);
SSD1306_Stopscroll();
SSD1306_ScrollRight(0x00, 0x0f);    // scroll entire screen right
msleep(2000);
SSD1306_Stopscroll();   // stop scrolling. If not done, screen will keep on scrolling
SSD1306_InvertDisplay(1);   // invert the display
msleep(2000);
SSD1306_InvertDisplay(0);  // normalize the display
msleep(2000);

 for(;;)
  {
 SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse1,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse2,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse3,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse4,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse5,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse6,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse7,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse8,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse9,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse10,128,64,1);
SSD1306_UpdateScreen();	
    msleep(20);

  }
}
