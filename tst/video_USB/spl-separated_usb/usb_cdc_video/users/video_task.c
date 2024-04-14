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
static 
	uint8_t frame_buffer[FRAME_WIDTH * FRAME_HEIGHT * 16 / 8];

uint32_t board_millis(void)
{
////  return os_time_get();
return 	sys_tick;
}
#if 0
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
#endif
static uint8_t tst_offs=0;

static void fill_color_bar(uint8_t *buffer, unsigned start_position)
{
	uint8_t btmp=0;
  /* EBU color bars
   * See also https://stackoverflow.com/questions/6939422 */
#if 1	
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
#endif	
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
extern uint8_t fb_y[];
////static 
extern	uint8_t fb_c[];

static void _fill_color_bar(uint8_t *buffer, unsigned start_position)
{
uint8_t *p;
	unsigned yy=0;
	unsigned cc=0;
uint32_t *pbuf;/////= (uint32_t *)&bar_color[4][0];
	p = &buffer[0];
for (unsigned i = 0; i < FRAME_HEIGHT; ++i) {
		for(unsigned j = 0; j < FRAME_WIDTH*2; j++)
		{
		*p++	= fb_y[yy];
		*p++	= fb_c[cc];
		yy++;	
		*p++	= fb_y[yy];
		*p++	= fb_c[cc];
		yy++;	
		cc++;
		}
			
	////		memset(p,*pbuf,FRAME_WIDTH * 2);
 ///// memcpy(p, buffer, FRAME_WIDTH * 2);
 /// p += FRAME_WIDTH * 2;
  }
}



void video_tsk(void)
{
  static unsigned start_ms = 0;
  static unsigned already_sent = 0;
////tu_printf("\r\n======video_task=============");

  if (!tud_video_n_streaming(0, 0)) {
    already_sent  = 0;
    frame_num     = 0;
    return;
  }
/////tu_printf("\r\n======video_task1=============");
	

  if (!already_sent) {
    already_sent = 1;
    start_ms = board_millis();
    fill_color_bar(frame_buffer, frame_num);
		
    tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
  }

  unsigned cur = board_millis();
  if (cur - start_ms < interval_ms) 
		return; // not enough time
  if (tx_busy) 
		return;
  start_ms += interval_ms;
/////tu_printf("\r\n======video_task2=============");

  fill_color_bar(frame_buffer, frame_num);
  tud_video_n_frame_xfer(0, 0, (void*)frame_buffer, FRAME_WIDTH * FRAME_HEIGHT * 16/8);
}

void video_task(void)
{
/////printf("\r\n======video_task=============");
	
/////	for(;;)
	{
	video_tsk()	;
	}
}


