///==========================================
#include <efxinc.h>
#include <f1c100s-irq.h>
#include <tusb.h>
#include <ctype.h>
#include "f1c100s_de.h"
#include "f1c100s_tvd.h"
#include "display.h"
#include "lcd.h"
#include "io.h"

extern void video_task(void);

////static uint8_t fb_y[720 * 576];
////static uint8_t fb_c[720 * 576];

static uint8_t fb_y[1000* 1000];
static uint8_t fb_c[1000 * 1000];


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
	}
}
///==================================================================
int tvin_init()
{
uint16_t tv_w, tv_h;
////tvd_init(TVD_MODE_UNKNOWN, fb_y, fb_c, 0);
////tvd_init(TVD_MODE_NTSC, fb_y, fb_c, 0);
////tvd_init(TVD_MODE_SECAM, fb_y, fb_c, 0);
tvd_init(TVD_MODE_PAL_B, fb_y, fb_c, 0);
///tvd_init(TVD_MODE_PAL_N, fb_y, fb_c, 0);
////tvd_init(TVD_MODE_PAL_M, fb_y, fb_c, 0);
	
  tvd_set_out_fmt(TVD_FMT_422_PL);
 //// tvd_set_out_fmt(TVD_FMT_422_PL|TVD_FMT_SWAP_UV);
 //// tvd_set_out_fmt(TVD_FMT_420_PL);
////  tvd_set_out_fmt(TVD_FMT_420_MB);
	
    tvd_get_out_size(&tv_w, &tv_h);
    tvd_set_bluescreen_mode(TVD_BLUE_OFF);

    defe_init_spl_422(tv_w, tv_h, fb_y, fb_c);

    debe_layer_init(0); // Layer 0 - video
    debe_layer_set_size(0, tv_w, tv_h);
    debe_layer_set_mode(0, DEBE_MODE_DEFE_VIDEO);
    debe_layer_enable(0);

    tvd_enable();
	
return 0;	
}
///==================================================================
void UserEntryInit(void)
{
	uint32_t *p_val;
target_wdt_feed();

printf("DDR Size: %uMB\n", (*(uint32_t*)0x5c) & 0xFFFFFF);
///===========================================
display_init();
display_set_bl(200);
debe_set_bg_color(0x0000FF00);
debe_load(DEBE_UPDATE_AUTO);
///==================================	
tvin_init();
///==================================	
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
///===========================================	
tusb_init();
	
////  printf("DDR size: %uMB\n", (*(uint32_t*)0x5c) & 0xFFFFFF);
	os_tsk_create(usb_task, 10);
  /////printf("time: %x\n", board_millis());
////	os_tsk_create(video_task, 8);
  /////printf("time1: %x\n", board_millis());
	
/////  printf("\n\rvideo_probe_and_commit_control_t [%u]\n", sizeof(video_probe_and_commit_control_t));
	
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| 函数名称 |: UserEntryLoop
//| 功能描述 |: 应用程序主循环
//|          |:
//| 参数列表 |:
//|          |:
//| 返    回 |:
//|          |:
//| 备注信息 |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
void UserEntryLoop(void)
{
  for (;;) {
    target_wdt_feed();
////		sys_delay(500);
		sys_delay(2);
////		  printf("time1: %x\n", board_millis());
video_task();
#if 0
    // 串口驱动测试
    if (f1c100s_uart_isTxEnd(UART0_MID)) {
      rCnt = f1c100s_uart_readFifo(UART0_MID, rbuffer, sizeof(rbuffer));
      if (rCnt > 0) {
        f1c100s_uart_asyncTx(UART0_MID, rbuffer, rCnt);
      }
    }
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////

