#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <dma.h>
#include <framebuffer.h>
#include <gpio-f1c100s.h>
#include <pwm-f1c100s.h>
#include "usb.h"

#define TEST_GPIO   0
#define TEST_PWM    0
#define TEST_FB     1

/* return_to_fel() - Return to BROM from SPL
 * @lr:		BROM link register value (return address)
 * @sp:		BROM stack pointer
 */
extern void sys_uart_putc(char c);
extern void return_to_fel(void);
typedef void (*go_fel_mode)(void);
render_t* render;
framebuffer_t fb_f1c100s;
pwm_t led_pwm =
{
	.virt = 0x01c21000,
	.duty = 40,
	.period = 40,
	.channel = 0,
	.polarity = 1,
	.pwm_port = &GPIO_PA,
	.pwm_pin = 2,
	.pwm_pin_cfg = 3,
};

int boot_main(int argc, char **argv) 
{
    
    /* Do initial mem pool */
	do_init_mem_pool();
    do_init_dma_pool();
    printf("Start main while!\n\r");
#if TEST_GPIO
    gpio_f1c100s_set_dir(&GPIO_PE, 2, GPIO_DIRECTION_OUTPUT);
    while(1)
    {
        gpio_f1c100s_set_value(&GPIO_PE, 2, 0);
        gpio_f1c100s_set_value(&GPIO_PE, 2, 1);
    }
#endif

#if TEST_FB

   {

       fb_f1c100s_init(&fb_f1c100s);
       render = fb_f1c100s_create(&fb_f1c100s);
       for (int i = 0; i < render->pixlen/4;i++)
       {
           ((uint32_t*)render->pixels)[i] = 0xFFFF0000;
       }
//        for (int i = 0; i < 810;i++)
//		{
//			((uint32_t*)render->pixels)[i] = 0xFF00FF00;
//		}
//        for (int i = render->pixlen/4-1; i > render->pixlen/4 - 10;i--)
//		   {
//			   ((uint32_t*)render->pixels)[i] = 0xFF0000FF;
//		   }
       fb_f1c100s_present(&fb_f1c100s, render);
       fb_f1c100s_setbl(&fb_f1c100s, 100);
   }
#endif

#if TEST_PWM
    pwm_t led_pwm_bl =
        {
            .virt = 0x01c21000,
            .duty = 50,
            .period = 1000000,
            .channel = 1,
            .polarity = true,
            .pwm_port = &GPIO_PE,
            .pwm_pin = 6,
            .pwm_pin_cfg = 3,
        };
    pwm_f1c100s_init(&led_pwm_bl);
#endif

    printf("Start main while!\n\r");
    // usb_device_init(USB_TYPE_USB_COM);

   	tv_in_decode_init(0);
   	volatile int dly;
    for(dly = 0;dly <10000000;dly++)
   	{
   		;;;
   	}
    tvd_debugdump(0);
//    //usb_reg_debugdump();//0x53555741
//    printf("render->pixlen:%d\n",render->pixlen);
//    printf("tvd_statues:0x%08x\n",tvd_get_status());

    RefleshLcdWithTVD((void*)0,800,600);
    while(1)
    {
//    	if(!gpio_f1c100s_get_value(&GPIO_PE, 10))
//    	{
//    		//go_fel_mode fel_entry =(go_fel_mode) 0x00000020 ;
//    		printf("return_to_fel>>>\n\n");
//    		while((!gpio_f1c100s_get_value(&GPIO_PE, 10)));
//
////    		char *sig = (char *)0xffff0004;
////			sig[0] = 'e';
////			sig[1] = 'G';
////			sig[2] = 'O';
////			sig[3] = 'N';
////			sig[4] = '.';
////			sig[5] = 'F';
////			sig[6] = 'E';
////			sig[7] = 'L';
//			return_to_fel();
////    		((void (*)(void))0xffff0040)();
//    		//fel_entry();
//    	}
    }
    return 0;
}

void RefleshLcdWithTVD(unsigned char *ydat,unsigned char * cbcr,int w,int h)
{
	int lcdw = 480;
	int i,j;
	int gray;
	unsigned char r = 0;
	unsigned int pos = 0;
	for ( i= 0; i < 272;i++)
	{
		for (j= 0; j < 480;j++)
		{
			int y = ydat[i*w+j];
			// float y16 = (float) ydat[i*w+j] - 16.0;

			// float cb128 = (float) cbcr[i/4*2*(w)+(j/2)*2] - 128.0;
			// float cr128 = (float) cbcr[(i/4*2)*(w)+j/2*2+1] - 128.0;

			// float r = 1.164*y16 + 1.596*cr128; //this might exceed 255
			// float g = 1.164*y16 - 0.813*cr128 - 0.391*cb128; //this could be less than 0 or greater than 255
			// float b = 1.164*y16 + 2.018*cb128; //this might exceed 255
			//YUV420 to RGB 
			int cb128 =  (int)cbcr[(i/4*2)*(w)+(j/2)*2] - 128;
			int cr128 =  (int)cbcr[(i/4*2)*(w)+j/2*2+1] - 128;
			int rdif = cr128 + ((cr128 * 103) >> 8);
			int invgdif = ((cb128 * 88) >> 8) +((cr128 * 183) >> 8);
			int bdif = cb128 +( (cb128*198) >> 8);
 
			int r = y + rdif;
			int g  = y - invgdif;
			int b = y + bdif;

			if(r > 255)
			{
				r = 255;
			}
			else if(r < 0)
			{
				r = 0;
			}
			if(g < 0)
			{
				g = 0;
			}
			else if(g > 255)
			{
				g = 255;
			}

			if(b > 255)
			{
				b = 255;
			}
			else if(b < 0)
			{
				b  = 0;
			}
			((uint32_t*)render->pixels)[i*lcdw + j] = 0xFF000000|((int)b<<16)|((int)g<<8)|((int)r<<0);
		}
	}
	fb_f1c100s_present(&fb_f1c100s, render);
}
void __fatal_error(const char *msg) {
    while (1);
}

#ifndef NDEBUG
void __assert_func(const char *file, int line, const char *func, const char *expr) {
    //printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

