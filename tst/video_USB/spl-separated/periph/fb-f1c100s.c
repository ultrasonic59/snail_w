/*
 * driver/fb-f1c100s.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "clk-f1c100s-pll.h"
#include "reset-f1c100s.h"
#include "gpio-f1c100s.h"
#include "pwm-f1c100s.h"
#include "framebuffer.h"
#include "f1c100s-gpio.h"
#include "f1c100s/reg-tcon.h"
#include "f1c100s/reg-defe.h"
#include "f1c100s/reg-debe.h"
#include "f1c100s/reg-ccu.h"
#include "lcd-cfg.h"
#include "io.h"

#define phys_to_virt(x) (x)

#if (LCD_PANEL_XSIZE == 800) && (LCD_PANEL_YSIZE == 600)
#define FB_LCD_XSIZE    (LCD_PANEL_XSIZE)
#define FB_LCD_YSIZE    (LCD_PANEL_YSIZE)
#define LCD_CTRL_BPP    (LCD_PANEL_BITPP)
#define LCD_BYTE_PP     (LCD_PANEL_BYTEPP)
#define PIXEL_CLOCK     (33000000)  // 大约67fps
#endif

#if (LCD_PANEL_XSIZE == 800) && (LCD_PANEL_YSIZE == 480)
#define FB_LCD_XSIZE    (LCD_PANEL_XSIZE)
#define FB_LCD_YSIZE    (LCD_PANEL_YSIZE)
#define LCD_CTRL_BPP    (LCD_PANEL_BITPP)
#define LCD_BYTE_PP     (LCD_PANEL_BYTEPP)
#define PIXEL_CLOCK     (33000000)  // 大约67fps
#endif

#if (LCD_PANEL_XSIZE == 480) && (LCD_PANEL_YSIZE == 272)
#define FB_LCD_XSIZE    (LCD_PANEL_XSIZE)
#define FB_LCD_YSIZE    (LCD_PANEL_YSIZE)
#define LCD_CTRL_BPP    (LCD_PANEL_BITPP)
#define LCD_BYTE_PP     (LCD_PANEL_BYTEPP)
#define PIXEL_CLOCK     (11000000)  // 大约57fps
#endif

typedef struct {
  uint32_t virtdefe;
  uint32_t virtdebe;
  uint32_t virttcon;

  char const* clkdefe;
  char const* clkdebe;
  char const* clktcon;
  int32_t rstdefe;
  int32_t rstdebe;
  int32_t rsttcon;
  int32_t width;
  int32_t height;
  int32_t pwidth;
  int32_t pheight;
  int32_t bits_per_pixel;
  int32_t bytes_per_pixel;
  int32_t index;
  void* vram[2];

  struct {
    int32_t pixel_clock_hz;
    int32_t h_front_porch;
    int32_t h_back_porch;
    int32_t h_sync_len;
    int32_t v_front_porch;
    int32_t v_back_porch;
    int32_t v_sync_len;
    int32_t h_sync_active;
    int32_t v_sync_active;
    int32_t den_active;
    int32_t clk_active;
  } timing;

  pwm_t* backlight;
  int32_t brightness;
} fb_f1c100s_priv_data_t;

static pwm_t led_pwm_bl = {
  .virt = 0x01c21000,
  .duty = 100,
  .period = 1000000,
  .channel = 1,
  .polarity = true,
  .pwm_port = &GPIO_PE,
  .pwm_pin = 6,
  .pwm_pin_cfg = 3,
};

static fb_f1c100s_priv_data_t fb_f1c100s_priv_object;
static uint32_t fb_mem[2][FB_LCD_XSIZE * FB_LCD_YSIZE / 4 * LCD_BYTE_PP] __attribute__((aligned(32)));

reset_f1c100s_t reset_1 = {
  .virt = 0x01c202c0,
  .base = 0,
  .nreset = 32,
};

reset_f1c100s_t reset_2 = {
  .virt = 0x01c202c4,
  .base = 32,
  .nreset = 32,
};

reset_f1c100s_t reset_3 = {
  .virt = 0x01c202d0,
  .base = 64,
  .nreset = 32,
};

static clk_pll_t clk_pll_video = {
  .virt = F1C100S_CCU_BASE,
  .parent = NULL,
  .channel = 2,
  .prate = 24000000, /* hosc */
};


inline static void f1c100s_debe_set_mode(fb_f1c100s_priv_data_t* pdat)
{
  struct f1c100s_debe_reg_t* debe = (struct f1c100s_debe_reg_t*)(pdat->virtdebe);
  uint32_t val;

  // enable debe
  val = read32((uint32_t)&debe->mode);
  val |= (1 << 0);
  write32((uint32_t)&debe->mode, val);

  // non-documentation
  write32((uint32_t)&debe->disp_size, (((pdat->height) - 1) << 16) | (((pdat->width) - 1) << 0));
  write32((uint32_t)&debe->layer0_size, (((pdat->height) - 1) << 16) | (((pdat->width) - 1) << 0));
#if LCD_CTRL_BPP == 16
  // Layer frame buffer line width in bits (16bits)
  write32((uint32_t)&debe->layer0_stride, ((pdat->width) << 4));
#else
  // Layer frame buffer line width in bits (32bits)
  write32((uint32_t)&debe->layer0_stride, ((pdat->width) << 5));
#endif

  // frame-buffer address in bits
  write32((uint32_t)&debe->layer0_addr_low32b, (uint32_t)(pdat->vram[pdat->index]) << 3);
  write32((uint32_t)&debe->layer0_addr_high4b, (uint32_t)(pdat->vram[pdat->index]) >> 29);
#if LCD_CTRL_BPP == 16
  // color 16-bpp (R:5/G:6/B:5) and  R/B channel swap
  write32((uint32_t)&debe->layer0_attr1_ctrl, (0x05 << 8) | (1 << 2));  /* 此处设置像素格式 */
#else
  // color 32-bpp (Padding:8/R:8/G:8/B:8) and  R/B channel swap
  write32((uint32_t)&debe->layer0_attr1_ctrl, (0x09 << 8) | (1 << 2));  /* 此处设置像素格式 */
#endif


  // enable layer-0
  val = read32((uint32_t)&debe->mode);
  val |= (1 << 8);
  write32((uint32_t)&debe->mode, val);

  // Register load control
  val = read32((uint32_t)&debe->reg_ctrl);
  val |= (1 << 0);
  write32((uint32_t)&debe->reg_ctrl, val);

  // Normal output channel Start & Reset control
  val = read32((uint32_t)&debe->mode);
  val |= (1 << 1);
  write32((uint32_t)&debe->mode, val);
}

inline static void f1c100s_debe_set_address(fb_f1c100s_priv_data_t* pdat, void* vram)
{
  struct f1c100s_debe_reg_t* debe = (struct f1c100s_debe_reg_t*)(pdat->virtdebe);

  write32((uint32_t)&debe->layer0_addr_low32b, (uint32_t)vram << 3);
  write32((uint32_t)&debe->layer0_addr_high4b, (uint32_t)vram >> 29);
}

inline static void f1c100s_tcon_enable(fb_f1c100s_priv_data_t* pdat)
{
  struct f1c100s_tcon_reg_t* tcon = (struct f1c100s_tcon_reg_t*)pdat->virttcon;
  uint32_t val;

  val = read32((uint32_t)&tcon->ctrl);
  val |= (1UL << 31);
  write32((uint32_t)&tcon->ctrl, val);
}

inline static void f1c100s_tcon_disable(fb_f1c100s_priv_data_t* pdat)
{
  struct f1c100s_tcon_reg_t* tcon = (struct f1c100s_tcon_reg_t*)pdat->virttcon;
  uint32_t val;

  write32((uint32_t)&tcon->ctrl, 0);
  write32((uint32_t)&tcon->int0, 0);

  val = read32((uint32_t)&tcon->tcon0_dclk);
  val &= ~(0xFUL << 28);
  write32((uint32_t)&tcon->tcon0_dclk, val);

  write32((uint32_t)&tcon->tcon0_io_tristate, 0xffffffff);
  write32((uint32_t)&tcon->tcon1_io_tristate, 0xffffffff);
}

inline static uint64_t f1c100s_tcon_clk_get_rate()
{
  return clk_f1c100s_pll_get_rate(&clk_pll_video, clk_pll_video.prate);
}

inline static void f1c100s_clk_pll_video_set_enable(bool enable)
{
  clk_f1c100s_pll_set_enable(&clk_pll_video, enable);
}

#define gate_clk_enable(virt, shift, invert)  write32(virt, (read32(virt) & ~(0x1U << shift)) | ((invert ? 0x0U : 0x1U) << shift))
#define gate_clk_disable(virt, shift, invert) write32(virt, (read32(virt) & ~(0x1U << shift)) | ((invert ? 0x1U : 0x0U) << shift))

inline static void f1c100s_clk_tcon_enable()
{
  // enable SCLK_GATING
  gate_clk_enable(0x01c20118, 31, false);
  // enable LCD_GATING
  gate_clk_enable(0x01c20064, 4, false);
}

inline static void f1c100s_clk_tcon_disable()
{
  gate_clk_disable(0x01c20118, 31, false);
  gate_clk_disable(0x01c20064, 4, false);
}

static void clk_divider_set_rate(uint32_t virt, uint32_t width, uint32_t shift, bool onebased, uint64_t prate, uint64_t rate)
{
  uint32_t mask = ((1 << (width)) - 1);
  uint32_t div;
  uint32_t val;

  if (rate == 0)
    rate = prate;

  div = prate / rate;
  if (onebased)
    div--;
  if (div > mask)
    div = mask;

  val = read32(virt);
  val &= ~(mask << shift);
  val |= div << shift;
  write32(virt, val);
}

static void clk_mux_set_parent(uint32_t virt, uint32_t width, uint32_t shift, uint32_t parent_val)
{
  uint32_t val;
  val = read32(virt);
  val &= ~(((1 << width) - 1) << shift);
  val |= parent_val << shift;
  write32(virt, val);
}

static void f1c100s_clk_defe_init(void)
{
  // select Clock Source for defe
  clk_mux_set_parent(0x01c2010c, 3, 24, 0);
  // set defe Clock divide ratio
  clk_divider_set_rate(0x01c2010c, 4, 0, true, f1c100s_tcon_clk_get_rate(), f1c100s_tcon_clk_get_rate());
}

inline static void f1c100s_clk_defe_enable()
{
  // enable SCLK_GATING
  gate_clk_enable(0x01c2010c, 31, false);
  // enable DEFE_GATING
  gate_clk_enable(0x01c20064, 14, false);
}

inline static void f1c100s_clk_defe_disable()
{
  gate_clk_disable(0x01c2010c, 31, false);
  gate_clk_disable(0x01c20064, 14, false);
}
// "clk-mux@0x01c2010c": {
//  "parent": [
//    { "name": "pll-video", "value": 0 },
//    { "name": "pll-periph", "value": 2 }
//  ],
//  "name": "mux-defe", "shift": 24, "width": 3,
//  "default": { "parent": "pll-video" }
// },
// "clk-divider@0x01c2010c": { "parent": "mux-defe", "name": "div-defe", "shift": 0, "width": 4, "default": { "rate": 198000000 } },
// "clk-gate@0x01c2010c": {"parent": "div-defe", "name": "gate-defe", "shift": 31, "invert": false },
// "clk-gate@0x01c20064": {"parent": "gate-defe", "name": "gate-bus-defe", "shift": 14, "invert": false },
// "clk-link": { "parent": "gate-bus-defe", "name": "link-defe" },

static void f1c100s_clk_debe_init(void)
{
  // select Clock Source for debe
  clk_mux_set_parent(0x01c20104, 3, 24, 0);
  // set debe Clock divide ratio
  clk_divider_set_rate(0x01c20104, 4, 0, true, f1c100s_tcon_clk_get_rate(), f1c100s_tcon_clk_get_rate());
}

// "clk-mux@0x01c20104": {
//  "parent": [
//    { "name": "pll-video", "value": 0 },
//    { "name": "pll-periph", "value": 2 }
//  ],
//  "name": "mux-debe", "shift": 24, "width": 3,
//  "default": { "parent": "pll-video" }
// },
// "clk-divider@0x01c20104": { "parent": "mux-debe", "name": "div-debe", "shift": 0, "width": 4, "divider-one-based": true, "default": { "rate": 198000000 } },
// "clk-gate@0x01c20104": {"parent": "div-debe", "name": "gate-debe", "shift": 31, "invert": false },
// "clk-gate@0x01c20064": {"parent": "gate-debe", "name": "gate-bus-debe", "shift": 12, "invert": false },
inline static void f1c100s_clk_debe_enable()
{
  // enable SCLK_GATING
  gate_clk_enable(0x01c20104, 31, false);
  // enable DEBE_GATING
  gate_clk_enable(0x01c20064, 12, false);
}

inline static void f1c100s_clk_debe_disable()
{
  gate_clk_disable(0x01c20104, 31, false);
  gate_clk_disable(0x01c20064, 12, false);
}

inline static void f1c100s_tcon_set_mode(fb_f1c100s_priv_data_t* pdat)
{
  struct f1c100s_tcon_reg_t* tcon = (struct f1c100s_tcon_reg_t*)pdat->virttcon;
  int32_t bp, total;
  uint32_t val;

  // use tcon0
  val = read32((uint32_t)&tcon->ctrl);
  val &= ~(0x1 << 0);
  write32((uint32_t)&tcon->ctrl, val);

  // set panel configurations
  val = (pdat->timing.v_front_porch + pdat->timing.v_back_porch + pdat->timing.v_sync_len);
  write32((uint32_t)&tcon->tcon0_ctrl, (1UL << 31) | ((val & 0x1f) << 4));

  //val = clk_get_rate(pdat->clktcon) / pdat->timing.pixel_clock_hz;
  val = f1c100s_tcon_clk_get_rate() / pdat->timing.pixel_clock_hz;
  write32((uint32_t)&tcon->tcon0_dclk, (0xFUL << 28) | (val << 0));

  // panel height and width
  write32((uint32_t)&tcon->tcon0_timing_active, ((pdat->width - 1) << 16) | ((pdat->height - 1) << 0));

  // 横向时序
  bp = pdat->timing.h_sync_len + pdat->timing.h_back_porch;
  total = pdat->width + pdat->timing.h_front_porch + bp;
  write32((uint32_t)&tcon->tcon0_timing_h, ((total - 1) << 16) | ((bp - 1) << 0));

  // 纵向时序
  bp = pdat->timing.v_sync_len + pdat->timing.v_back_porch;
  total = pdat->height + pdat->timing.v_front_porch + bp;
  write32((uint32_t)&tcon->tcon0_timing_v, ((total * 2) << 16) | ((bp - 1) << 0));

  // 同步信号宽度
  write32((uint32_t)&tcon->tcon0_timing_sync, ((pdat->timing.h_sync_len - 1) << 16) | ((pdat->timing.v_sync_len - 1) << 0));

  // 这里要注意，可能跟bpp有关？
  write32((uint32_t)&tcon->tcon0_hv_intf, 0);
  write32((uint32_t)&tcon->tcon0_cpu_intf, 0);

  if (pdat->bits_per_pixel == 18 || pdat->bits_per_pixel == 16) {
    write32((uint32_t)&tcon->tcon0_frm_seed[0], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_seed[1], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_seed[2], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_seed[3], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_seed[4], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_seed[5], 0x11111111);
    write32((uint32_t)&tcon->tcon0_frm_table[0], 0x01010000);
    write32((uint32_t)&tcon->tcon0_frm_table[1], 0x15151111);
    write32((uint32_t)&tcon->tcon0_frm_table[2], 0x57575555);
    write32((uint32_t)&tcon->tcon0_frm_table[3], 0x7f7f7777);
    write32((uint32_t)&tcon->tcon0_frm_ctrl, (pdat->bits_per_pixel == 18) ? ((1UL << 31) | (0 << 4)) : ((1UL << 31) | (5 << 4)));
  }

  val = (1 << 28);
  if (!pdat->timing.h_sync_active)
    val |= (1 << 25);
  if (!pdat->timing.h_sync_active)
    val |= (1 << 24);
  write32((uint32_t)&tcon->tcon0_io_polarity, val);
  write32((uint32_t)&tcon->tcon0_io_tristate, 0);
}

inline static void fb_f1c100s_cfg_gpios(const gpio_port_t* port, int32_t pin_start, int32_t pin_end, int32_t cfg, gpio_pull_t pull, gpio_drv_t drv)
{
  int32_t pin;
  for (pin = pin_start; pin < pin_end; pin++) {
    gpio_f1c100s_set_cfg(port, pin, cfg);
    gpio_f1c100s_set_pull(port, pin, pull);
    gpio_f1c100s_set_drv(port, pin, drv);
  }
}

static void fb_f1c100s_init_hw(fb_f1c100s_priv_data_t* pdat)
{
  // enable PLL_ENABLE bit in PLL_VEDIO register
  f1c100s_clk_pll_video_set_enable(true);
  f1c100s_clk_debe_init();
  f1c100s_clk_defe_init();

  // Set LCD panel pin-function
#ifdef PCB_TINY200V2
  fb_f1c100s_cfg_gpios(&GPIO_PD, 1, 12, 0x2, GPIO_PULL_NONE, GPIO_DRV_STRONG);
  fb_f1c100s_cfg_gpios(&GPIO_PD, 13, 22, 0x2, GPIO_PULL_NONE, GPIO_DRV_STRONG);
#else
  fb_f1c100s_cfg_gpios(&GPIO_PD, 0, 22, 0x2, GPIO_PULL_NONE, GPIO_DRV_STRONG);
#endif

  // disable/initialize tcon0
  f1c100s_tcon_disable(pdat);

  f1c100s_debe_set_mode(pdat);
  f1c100s_tcon_set_mode(pdat);
  f1c100s_tcon_enable(pdat);

  // enable panel back-light
  pwm_f1c100s_init(pdat->backlight);
}

void fb_f1c100s_setbl(framebuffer_t* fb, int32_t brightness)
{
  fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;
  //led_set_brightness(pdat->backlight, brightness);
  pwm_f1c100s_set_duty(pdat->backlight, brightness);
}

int32_t fb_f1c100s_getbl(framebuffer_t* fb)
{
  fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;
  // return led_get_brightness(pdat->backlight);
  return pwm_f1c100s_get_duty(pdat->backlight);
}
#if 1
render_t * fb_f1c100s_create(framebuffer_t * fb)
{
	fb_f1c100s_priv_data_t * pdat = (fb_f1c100s_priv_data_t *)fb->priv;
	render_t * render;

__align(4)	uint8_t *pixels;
	size_t pixlen;

	pixlen = pdat->width * pdat->height * pdat->bytes_per_pixel;
	////pixels = memalign(4, pixlen);
		pixels = (uint8_t *)malloc(pixlen);
#if 1		
	if(!pixels)
		{
			return NULL;
		}

	render = malloc(sizeof(render_t));
	if(!render)
	{
		free(pixels);
		return NULL;
	}

	render->width = pdat->width;
	render->height = pdat->height;
	render->pitch = (pdat->width * pdat->bytes_per_pixel + 0x3) & ~0x3;
	render->format = PIXEL_FORMAT_ARGB32;
	render->pixels = pixels;
	render->pixlen = pixlen;
	render->priv = NULL;
#endif
	return render;
}
#endif

void fb_f1c100s_destroy(framebuffer_t * fb, render_t * render)
{
	if(render)
	{
		free(render->pixels);
		free(render);
	}
}


void fb_f1c100s_present(framebuffer_t* fb, int index)
{
  fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;

  if (pdat && (index == 0 || index == 1)) {
    f1c100s_debe_set_address(pdat, pdat->vram[index]);
  }
}

void fb_f1c100s_init(framebuffer_t* fb)
{
  int32_t i;
  fb_f1c100s_priv_data_t* pdat = &fb_f1c100s_priv_object;

  pdat->virtdefe = phys_to_virt(F1C100S_DEFE_BASE);
  pdat->virtdebe = phys_to_virt(F1C100S_DEBE_BASE);
  pdat->virttcon = phys_to_virt(F1C100S_TCON_BASE);
  pdat->clkdefe = "clkdefe";
  pdat->clkdebe = "clkdebe";
  pdat->clktcon = "clktcon";
  pdat->rstdefe = 46;
  pdat->rstdebe = 44;
  pdat->rsttcon = 36;
  pdat->width = FB_LCD_XSIZE;
  pdat->height = FB_LCD_YSIZE;
  pdat->pwidth = 216;
  pdat->pheight = 135;
  pdat->bits_per_pixel = LCD_CTRL_BPP;
  pdat->bytes_per_pixel = LCD_BYTE_PP;
  pdat->index = 0;
  pdat->vram[0] = fb_mem[0];
  pdat->vram[1] = fb_mem[1];

  // hclock = 40+87+1+width=128+width;
  // vlines = 13+31+1+height=45+height;
  pdat->timing.pixel_clock_hz = PIXEL_CLOCK;
  pdat->timing.h_front_porch = 40;
  pdat->timing.h_back_porch = 87;
  pdat->timing.h_sync_len = 1;
  pdat->timing.v_front_porch = 13;
  pdat->timing.v_back_porch = 31;
  pdat->timing.v_sync_len = 1;
  pdat->timing.h_sync_active = false;
  pdat->timing.v_sync_active = false;
  pdat->timing.den_active = false;
  pdat->timing.clk_active = false;
  pdat->backlight = &led_pwm_bl;

  fb->name = "fb-f1c100s";
  fb->width = pdat->width;
  fb->height = pdat->height;
  fb->pwidth = pdat->pwidth;
  fb->pheight = pdat->pheight;
  fb->bpp = pdat->bytes_per_pixel * 8;
  fb->priv = pdat;

  f1c100s_clk_defe_enable();
  f1c100s_clk_debe_enable();
  f1c100s_clk_tcon_enable();

  if (pdat->rstdefe >= 0) // De-assert DEFE_RST
    reset_f1c100s_deassert(&reset_2, pdat->rstdefe - reset_2.base);
  if (pdat->rstdebe >= 0) // De-assert DEBE_RST
    reset_f1c100s_deassert(&reset_2, pdat->rstdebe - reset_2.base);
  if (pdat->rsttcon >= 0) // De-assert LCD_RST
    reset_f1c100s_deassert(&reset_2, pdat->rsttcon - reset_2.base);

  // F1C100S_DEBE_BASE寄存器组全清零
  for (i = 0x0800; i < 0x1000; i += 4)
    write32(pdat->virtdebe + i, 0);

  // 开始配置LCD控制器
  fb_f1c100s_init_hw(pdat);
  f1c100s_debe_set_address(pdat, pdat->vram[0]);
}

void* fb_f1c100s_get_vram1(void)
{
  return fb_mem[0];
}

void* fb_f1c100s_get_vram2(void)
{
  return fb_mem[1];
}

void fb_f1c100s_remove(framebuffer_t* fb)
{
  //fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;

  if (fb) {
    f1c100s_clk_defe_disable();
    f1c100s_clk_debe_disable();
    f1c100s_clk_tcon_disable();
  }
}

void fb_f1c100s_suspend(framebuffer_t* fb)
{
  fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;

  //pdat->brightness = led_get_brightness(pdat->backlight);
  pdat->brightness = pwm_f1c100s_get_duty(pdat->backlight);
  //led_set_brightness(pdat->backlight, 0);
  pwm_f1c100s_set_duty(pdat->backlight, 0);
}

void fb_f1c100s_resume(framebuffer_t* fb)
{
  fb_f1c100s_priv_data_t* pdat = (fb_f1c100s_priv_data_t*)fb->priv;

  //led_set_brightness(pdat->backlight, pdat->brightness);
  pwm_f1c100s_set_duty(pdat->backlight, pdat->brightness);
}
