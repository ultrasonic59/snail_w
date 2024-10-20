///==========================================
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
#include "irq_misc.h"
#include "misc.h"

extern void video_task(void);

////static uint8_t fb_y[720 * 576];
////static uint8_t fb_c[720 * 576];

////static 
	uint8_t fb_y[720* 576];
////static 
	uint8_t fb_c[720 * 576];


#if 0
// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case
static void echo_serial_port(uint8_t itf, uint8_t buf[], uint32_t count)
{
  for(uint32_t i=0; i<count; i++)
  {
    if (itf == 0)
    {
      // echo back 1st port as lower case
      if (isupper(buf[i])) buf[i] += 'a' - 'A';
    }
    else
    {
      // echo back 2nd port as upper case
      if (islower(buf[i])) buf[i] -= 'a' - 'A';
    }

    tud_cdc_n_write_char(itf, buf[i]);
  }
  tud_cdc_n_write_flush(itf);
}
#endif
uint8_t buf[512];
#if 0
void tud_cdc_rx_cb(uint8_t itf) {
	uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));

	// echo back to both serial ports
	echo_serial_port(itf, buf, count);
}
#endif
__task void usb_task() {
  for (;;) {
		tud_task();
		sys_delay(2);

	}
}
extern void tvd_irq_handle(void);

///==================================================================
int tvin_init()
{
uint16_t tv_w, tv_h;
tvd_init(TVD_MODE_PAL_B, fb_y, fb_c, 0);
tvd_set_out_fmt(TVD_FMT_422_PL);
	
    tvd_get_out_size(&tv_w, &tv_h);
	
		printf("tvin_init Size: [%u][%u]\n", tv_w,tv_h);
	
    tvd_set_bluescreen_mode(TVD_BLUE_OFF);

 ////   defe_init_spl_422(tv_w, tv_h, fb_y, fb_c);
   defe_init_spl_422(tv_w, tv_h, fb_y, fb_c);

    debe_layer_init(0); // Layer 0 - video
    debe_layer_set_size(0, tv_w, tv_h);
		
    debe_layer_set_mode(0, DEBE_MODE_DEFE_VIDEO);
 ////   debe_layer_set_mode(0, DEBE_MODE_YUV);
		
    debe_layer_enable(0);
    tvd_enable();
  f1c100s_intc_set_isr(F1C100S_IRQ_TVD, tvd_irq_handle);
  f1c100s_intc_enable_irq(F1C100S_IRQ_TVD);
	
return 0;	
}
////=====================================================================
////render_t* render;
////framebuffer_t fb_f1c100s;

extern void lcd_task(void);

#define TEST_FB 0
///==================================================================
void UserEntryInit(void)
{
/////uint32_t *p_val;
////uint8_t btst=0;	
target_wdt_feed();

printf("DDR size: %uMB\n", (*(uint32_t*)0x5c) & 0xFFFFFF);
///===========================================
init_test1_pin();
	#if 0
for(;;)
	{
	put_test1_pin(btst)	;
	btst++;
	sys_delay(5);
	}
	#endif
#if 1	
display_init();
display_set_bl(100);
debe_set_bg_color(0xFF000000);
debe_load(DEBE_UPDATE_AUTO);
#endif
///==================================	
 tvin_init();
///==================================	
#if 1	
    lcd_init(1); // Layer 1 - overlay
 ////   lcd_init(0); // Layer 1 - overlay
    lcd_fill(0, 0, DISPLAY_W, DISPLAY_H, COLOR_TRANSPARENT);
    lcd_set_bg_color(0x80088000);
    lcd_set_text_color(COLOR_WHITE);
    lcd_set_text_pos(300, 0);
    lcd_printf("====== PAL==========");
#if 0		
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
		#endif
#endif
///===========================================
////	os_tsk_create(lcd_task, 11);

tusb_init();
	
////  printf("DDR size: %uMB\n", (*(uint32_t*)0x5c) & 0xFFFFFF);
////	os_tsk_create(usb_task, 8);
	os_tsk_create(test_thr, 10);
	
  /////printf("time: %x\n", board_millis());
////	os_tsk_create(video_task, 8);
  /////printf("time1: %x\n", board_millis());
/////	os_tsk_create(video_task, 10);
	
/////  printf("\n\rvideo_probe_and_commit_control_t [%u]\n", sizeof(video_probe_and_commit_control_t));
	
}
extern void video_tsk(void);
extern	uint8_t frame_buffer[];

////////////////////////////////////////////////////////////////////////////////
#define BEG_POS 880
void UserEntryLoop(void)
{
	uint32_t *p_val=(uint32_t *)fb_y;
////	uint32_t val;
	uint32_t ii;
		uint32_t jj;
			for(ii=0;ii<16;ii++)
				{
			  p_val[BEG_POS+ii]=0;
				}

  for (;;) {
    target_wdt_feed();
////		sys_delay(500);
		sys_delay(2);
		video_tsk();
		
	////	  printf("time1: %x\n", board_millis());
		#if 1
/////while(1) 
	{
        lcd_set_text_pos(500, 0);
	#if 0	
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
		#endif
	////====================================

	#if 1
		#if 0	
		for(ii=0;ii<720* 576;ii++)
				{
			  fb_c[ii]=0xff;
				}
////fb_y[720* 576]
				for(ii=0;ii<720* 576;ii++)
				{
			  if(fb_c[ii]!=0xff)
					break;
				}
	#endif	
	ii=576*2 +14;
			for(jj=0;jj<16;jj++)
				{
			  ////val = p_val[BEG_POS+ii];
        lcd_printf("[%x]%02X\n",jj+ii,fb_c[ii+jj]);
				}
	#endif	
	    }
	#endif
  }
}


////////////////////////////////////////////////////////////////////////////////

