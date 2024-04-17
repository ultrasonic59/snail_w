// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#ifndef __LIB_F1C100S_H__
#define __LIB_F1C100S_H__

#include <stdint.h>
#include <ftypes.h>

// �������ԣ�F1C100s��[0x00000000-0x0000b5ff]�ռ���45.5kB��SRAM��
// ��[0x00010000-0x00019FFF]����������40kB��SRAM A������datashit��

// spiflash����ʱ��BROM���û���spl���ص�0x00000000��SRAM�ռ䡿��ַ��
// �ٰѶ�ջָ��SP����Ϊ0x00009FF4��Ȼ����ת��spl���롣

// spiflash����ʱ��CPU����SVCģʽ��IRQ��FIQ���رգ�

// ����fel�������У�spl�ĵ�ַ��Ȼ��0x00000000����SP��0x0000B418

#ifdef __cplusplus
extern "C" {
#endif

#define CLK_CPU     (720*1000000UL)
#define CLK_PERI    (600*1000000UL)
#define CLK_AHB     (200*1000000UL)
#define CLK_APB     (100*1000000UL)

/* types declared by <f1c100s-intc.c> */

typedef void (*IRQHandleTypeDef)(void);

extern uint8_t   f1c100s_intc_get_nirq(void);
extern void      f1c100s_intc_dispatch(uint8_t nIRQ);
extern void      f1c100s_intc_set_isr(uint8_t nIRQ, void (*handle)(void));
extern void      f1c100s_intc_enable_irq(uint8_t nIRQ);
extern uint8_t   f1c100s_intc_check_irq(uint8_t nIRQ);
extern void      f1c100s_intc_disable_irq(uint8_t nIRQ);
extern void      f1c100s_intc_unmask_irq(uint8_t nIRQ);
extern void      f1c100s_intc_mask_irq(uint8_t nIRQ);
extern void      f1c100s_intc_force_irq(uint8_t nIRQ);
extern void      f1c100s_intc_clear_pend(uint8_t nIRQ);
extern void      f1c100s_intc_init(void);

#define I2C_M_TEN           0x0010    /* this is a ten bit chip address */
#define I2C_M_RD            0x0001    /* read data, from slave to master */
#define I2C_M_NOSTART       0x4000    /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR  0x2000    /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK    0x1000    /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK     0x0800    /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN      0x0400    /* length will be first received byte */

typedef struct {
  uint16_t addr;      /* slave address            */
  uint16_t flags;     /* message flags I2C_M_XX   */
  uint16_t len;       /* msg length               */
  uint8_t* buf;       /* pointer to msg data      */
} I2CMsg_TypeDef;

#define TWI0_MID    (0)
#define TWI1_MID    (1)
#define TWI2_MID    (2)

/* types declared by <f1c100s-iic.c> */
void      f1c100s_twi_init(uint8_t mid, uint32_t freq);
int       f1c100s_twi_xfer(uint8_t mid, I2CMsg_TypeDef msgs[], int num);


#define UART0_MID   (0)
#define UART1_MID   (1)
#define UART2_MID   (2)

/* types declared by <f1c100s-uart.c> */
extern bool_t   f1c100s_uart_init(uint8_t mid);
extern int      f1c100s_uart_readFifo(uint8_t mid, uint8_t buf[], unsigned int max);
extern void     f1c100s_uart_clearfifo(uint8_t mid);
extern void     f1c100s_uart_setBaudrate(uint8_t mid, uint32_t baud);
extern uint32_t f1c100s_uart_getBaudrate(uint8_t mid);
extern void     f1c100s_uart_setRxCallback(uint8_t mid, void (*pf)(void));
extern void     f1c100s_uart_setTxCallback(uint8_t mid, void (*pf)(void));
extern void     f1c100s_uart_asyncTx(uint8_t mid, const void* ptr, unsigned int len);
extern bool_t   f1c100s_uart_isTxEnd(uint8_t mid);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_F1C100S_H__ */