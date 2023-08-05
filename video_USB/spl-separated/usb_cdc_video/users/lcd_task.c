#include <efxinc.h>
#include <f1c100s-irq.h>
#include <tusb.h>
#include <ctype.h>
#include "f1c100s_de.h"
#include "f1c100s_tvd.h"
#include "lcd-cfg.h"

#include "display.h"
#include "lcd.h"
#include "io.h"
#include "framebuffer.h"
#include "tvd.h"

extern uint8_t fb_y[1];
extern uint8_t fb_c[];
 
void lcd_task(void)
{
uint32_t *p_val;
	
lcd_init(1); // Layer 1 - overlay
 ////   lcd_init(0); // Layer 1 - overlay
    lcd_fill(0, 0, DISPLAY_W, DISPLAY_H, COLOR_TRANSPARENT);
    lcd_set_bg_color(0x80000000);
    lcd_set_text_color(COLOR_WHITE);
    lcd_set_text_pos(200, 0);
    lcd_printf("PAL");
while(1) {
        lcd_set_text_pos(600, 0);
        uint32_t val = read32(TVD_BASE + TVD_STATE_0);
        lcd_printf("%08lX\n", val);
        val = read32(TVD_BASE + TVD_STATE_1);
        lcd_printf("%08lX\n", val);
        val = read32(TVD_BASE + TVD_STATE_2);
        lcd_printf("ST2=%08lX\n", val);
        val = read32(TVD_BASE + TVD_STATE_3);
        lcd_printf("%08lX\n", val);
        val = read32(TVD_BASE + TVD_STATE_4);
        lcd_printf("%08lX\n", val);
	////====================================
	p_val= (uint32_t *)&fb_c[4420];
        val = *p_val;
        lcd_printf("%08lX\n", val);
	p_val= (uint32_t *)&fb_y[4420];
        val = *p_val;
        lcd_printf("%08lX\n", val);
    }
}

