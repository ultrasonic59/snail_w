#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tusb.h"
#include "usb_descriptors.h"
#include "bsp/board.h"
#include "efxinc.h"

///==========================================
static unsigned tx_busy = 0;
static unsigned frame_num = 0;
static unsigned interval_ms = 1000 / FRAME_RATE;
static uint8_t frame_buffer[FRAME_WIDTH * FRAME_HEIGHT * 16 / 8];

uint32_t board_millis(void)
{
////  return os_time_get();
return 	sys_tick;
}
static uint8_t tst_offs=0;

static void fill_color_bar(uint8_t *buffer, unsigned start_position)
{
	uint8_t btmp=0;
  /* EBU color bars
   * See also https://stackoverflow.com/questions/6939422 */
  static uint8_t const bar_color[8][4] = {
    /*  Y,   U,   Y,   V */
    { 235, 128, 235, 128}, /* 100% White */
    { 219,  16, 219, 138}, /* Yellow */
    { 188, 154, 188,  16}, /* Cyan */
    { 173,  42, 173,  26}, /* Green */
    {  78, 214,  78, 230}, /* Magenta */
    {  63, 102,  63, 240}, /* Red */
    {  32, 240,  32, 118}, /* Blue */
    {  16, 128,  16, 128}, /* Black */
  };
  uint8_t *p;

  /* Generate the 1st line */
  uint8_t *end = &buffer[FRAME_WIDTH * 2];
  unsigned idx = (FRAME_WIDTH / 2 - 1) - (start_position % (FRAME_WIDTH / 2));
  p = &buffer[idx * 4];
  for (unsigned i = 0; i < 8; ++i) {
    for (int j = 0; j < FRAME_WIDTH / (2 * 8); ++j) {
			btmp=i+tst_offs;
			btmp&=0x7;
      memcpy(p, &bar_color[btmp], 4);
      p += 4;
      if (end <= p) {
        p = buffer;
      }
    }
  }
  /* Duplicate the 1st line to the others */
  p = &buffer[FRAME_WIDTH * 2];
  for (unsigned i = 1; i < FRAME_HEIGHT; ++i) {
    memcpy(p, buffer, FRAME_WIDTH * 2);
    p += FRAME_WIDTH * 2;
  }
	tst_offs++;
}



void video_task(void)
{
  static unsigned start_ms = 0;
  static unsigned already_sent = 0;
/////tu_printf("\r\n======video_task=============");

  if (!tud_video_n_streaming(0, 0)) {
    already_sent  = 0;
    frame_num     = 0;
    return;
  }
/////tu_printf("\r\n======video_task1=============");

  if (!already_sent) {
    already_sent = 1;
    start_ms = board_millis();
#ifdef CFG_EXAMPLE_VIDEO_READONLY
# if defined(CFG_EXAMPLE_VIDEO_DISABLE_MJPG)
    tud_video_n_frame_xfer(0, 0, (void*)(uintptr_t)&frame_buffer[(frame_num % (FRAME_WIDTH / 2)) * 4],
                           FRAME_WIDTH * FRAME_HEIGHT * 16/8);
# else
    tud_video_n_frame_xfer(0, 0, (void*)(uintptr_t)frames[frame_num % 8].buffer, frames[frame_num % 8].size);
# endif
#else
    fill_color_bar(frame_buffer, frame_num);
    tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
#endif
  }

  unsigned cur = board_millis();
  if (cur - start_ms < interval_ms) 
		return; // not enough time
  if (tx_busy) 
		return;
  start_ms += interval_ms;
/////tu_printf("\r\n======video_task2=============");

#ifdef CFG_EXAMPLE_VIDEO_READONLY
# if defined(CFG_EXAMPLE_VIDEO_DISABLE_MJPG)
  tud_video_n_frame_xfer(0, 0, (void*)(uintptr_t)&frame_buffer[(frame_num % (FRAME_WIDTH / 2)) * 4],
                         FRAME_WIDTH * FRAME_HEIGHT * 16/8);
# else
  tud_video_n_frame_xfer(0, 0, (void*)(uintptr_t)frames[frame_num % 8].buffer, frames[frame_num % 8].size);
# endif
#else
  fill_color_bar(frame_buffer, frame_num);
  tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
	
#endif
}
