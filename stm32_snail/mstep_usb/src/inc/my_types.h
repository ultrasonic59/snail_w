#ifndef __MY_TYPES_H__
#define __MY_TYPES_H__

#include <intrinsics.h>

typedef __istate_t atomic_t;

static inline atomic_t atomic_begin(void)
{
	__istate_t a = __get_interrupt_state();
	__disable_interrupt();
	return a;
}

static inline void atomic_end(atomic_t a)
{
	__set_interrupt_state(a);
}

typedef struct usb_req_s
{
uint32_t addr_dev;
uint8_t num_point;
uint8_t in_out;         ///1 -in ,0 -out
}usb_req_t;

#ifndef MIN
#define MIN(a,b) (a<b?a:b)
#endif
typedef void (*void_fn_void)(void);

typedef void (*void_fn_u8)(uint8_t);
typedef void (*void_fn_int)(int);
typedef void (*void_fn_pvoid)(void*);
typedef int (*int_fn_u8_pvoid)(uint8_t,void *);
typedef int (*int_fn_pvoid)(void*);
typedef int (*int_fn_void)(void);
typedef uint8_t (*u8_fn_void)(void);
typedef uint8_t (*u8_fn_u8)(uint8_t);
typedef uint16_t (*u16_fn_void)(void);
typedef uint16_t (*u16_fn_pu8)(uint8_t*);
typedef uint16_t (*u16_fn_u8_pu8)(uint8_t,uint8_t*);
typedef uint16_t (*u16_fn_u8_u16_pu8)(uint8_t,uint16_t,uint8_t*);
///typedef void (*void_fn_int)(int);
///typedef void (*void_fn_pvoid)(void*);
typedef uint32_t (*u32_fn_void)(void);
typedef int16_t (*s16_fn_void)(void);
typedef uint32_t (*u32_fn_s16)(int16_t);
typedef void* (*pvoid_fn_void)(void);
typedef int32_t (*s32_fn_void)(void);
typedef void (*void_fn_u8_pvoid)(uint8_t,void *);
typedef uint8_t (*u8_fn_pvoid_pu8_u16)(void*,uint8_t*,uint16_t);
typedef uint8_t (*u8_fn_pu8_u16)(uint8_t*,uint16_t);

#define msleep vTaskDelay

#endif