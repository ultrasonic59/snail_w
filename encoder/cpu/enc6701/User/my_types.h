#ifndef _MY_TYPES_H__
#define _MY_TYPES_H__
///=================================================
#include <stdint.h>
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
typedef uint32_t (*u32_fn_void)(void);
typedef int16_t (*s16_fn_void)(void);
typedef uint32_t (*u32_fn_s16)(int16_t);
typedef void* (*pvoid_fn_void)(void);
typedef int32_t (*s32_fn_void)(void);
typedef void (*void_fn_u8_pvoid)(uint8_t,void *);
typedef uint8_t (*u8_fn_pvoid_pu8_u16)(void*,uint8_t*,uint16_t);
typedef uint8_t (*u8_fn_pu8_u16)(uint8_t*,uint16_t);

#define NUM_PAR_CMD 3
typedef struct task_cmd_
{
uint8_t  cmd;
uint8_t  drv;
uint32_t par[NUM_PAR_CMD];
}task_cmd_t;

typedef struct __attribute__((packed)) contr_status_
{
int16_t coord_x;
uint16_t coord_z;                  ///
uint16_t coord_rot;                  ///
uint16_t conc;                  ///
uint16_t status;    ///
uint16_t reserv[3];    ///
}contr_status_t;

#define BIT_CON_SERVO_X     (0x1<<0)
#define BIT_CON_SERVO_AY     (0x1<<1)
#define BIT_CON_SERVO_Z     (0x1<<2)
#define BIT_CON_SERVO_ROT   (0x1<<3)
#define BIT_KLP_MOVE        (0x1<<4)
#define BIT_ERROR_SERVO     (0x1<<5)
#define BIT_X_OK            (0x1<<6)
#define BIT_X_DIR           (0x1<<7)
#define FLAG_X_END_GO       (0x1<<8)
#define BIT_Z_OK            (0x1<<9)
#define BIT_Z_DIR           (0x1<<10)
#define FLAG_Z_END_GO       (0x1<<11)

/*
typedef struct __attribute__((packed)) dp_dat_s
{
uint8_t flags;  
int16_t dp_al;
int16_t dp_ar;
int16_t dp_bl;
int16_t dp_br;
}dp_dat_t;
*/
#if 0
__packed typedef struct par_strb_s
{
uint8_t on_strb;
uint8_t	por;
////u16 offs_type;	///
uint8_t dn_up;	///1- down 0 - up
uint8_t on_vibro;	///1-on ,o-off
uint16_t beg;
uint16_t len;
}par_strb_t;
#endif
///====================
#endif	///_MY_TYPES_H__
