#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum 
{
	PIXEL_FORMAT_ARGB32		= 0,
	PIXEL_FORMAT_RGB24		= 1,
	PIXEL_FORMAT_A8			= 2,
	PIXEL_FORMAT_A1			= 3,
	PIXEL_FORMAT_RGB16_565	= 4,
	PIXEL_FORMAT_RGB30		= 5,
}pixel_format_t;


typedef struct render_st{
	/* The width of render */
	uint32_t width;

	/* The height of render */
	uint32_t height;

	/* The pitch of one scan line */
	uint32_t pitch;

	/* Pixel format */
	pixel_format_t format;

	/* Pixel data */
	void * pixels;

	/* Pixel data length */
	size_t pixlen;

	/* Private data */
	void * priv;
}render_t;

typedef struct framebuffer_st {
  /* Framebuffer name */
  char* name;

  /* The width and height in pixel */
  int32_t width, height;

  /* The physical size in millimeter */
  int32_t pwidth, pheight;

  /* The bit per pixel */
  int32_t bpp;

  /* Private data */
  void* priv;
} framebuffer_t;

void    fb_f1c100s_setbl(framebuffer_t* fb, int32_t brightness);

int32_t fb_f1c100s_getbl(framebuffer_t* fb);

void    fb_f1c100s_init(framebuffer_t* fb);

void    fb_f1c100s_remove(framebuffer_t* fb);

void    fb_f1c100s_suspend(framebuffer_t* fb);

void    fb_f1c100s_resume(framebuffer_t* fb);

void*   fb_f1c100s_get_vram1(void);

void*   fb_f1c100s_get_vram2(void);

void    fb_f1c100s_present(framebuffer_t* fb, int index);

#ifdef __cplusplus
}
#endif

#endif /* __FRAMEBUFFER_H__ */
