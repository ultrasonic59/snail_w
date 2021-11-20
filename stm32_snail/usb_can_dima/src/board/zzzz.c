#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

////#include "stm32f2xx_gpio.h"
#include "board.h"
#include "my_grbl.h"
#include "printk.h"

////#define TEST_PIN ZSTP_PIN
////#define TEST_PIN_GPIO ZSTP_PIN_GPIO

void  put_tst1_pin(uint8_t idat)
{
#if 1  
if(idat&0x1)
  {
  GPIO_SetBits(TST1_PIN_GPIO, TST1_PIN);
   }
else
  {
   GPIO_ResetBits(TST1_PIN_GPIO, TST1_PIN);
  }
#endif 
}

void  put_tst2_pin(uint8_t idat)
{
#if 1  
if(idat&0x1)
  {
   GPIO_SetBits(TST2_PIN_GPIO, TST2_PIN);
  ////GPIO_SetBits(TST7_PIN_GPIO, TST7_PIN);
  }
else
  {
   GPIO_ResetBits(TST2_PIN_GPIO, TST2_PIN);
   ////GPIO_ResetBits(TST7_PIN_GPIO, TST7_PIN);
  }
#endif 
}
void  put_tst3_pin(uint8_t idat)
{
#if 1  
if(idat&0x1)
  {
  GPIO_SetBits(TST3_PIN_GPIO, TST3_PIN);
  ////GPIO_SetBits(TST7_PIN_GPIO, TST7_PIN);
  }
else
  {
   GPIO_ResetBits(TST3_PIN_GPIO, TST3_PIN);
   ////GPIO_ResetBits(TST7_PIN_GPIO, TST7_PIN);
  }
#endif 
}
void  _put_tst_pin(uint8_t idat)
{
#if 1  
if(idat&0x1)
  {
  GPIO_SetBits(TST3_PIN_GPIO, TST3_PIN);
   GPIO_SetBits(TST2_PIN_GPIO, TST2_PIN);
  ////GPIO_SetBits(TST7_PIN_GPIO, TST7_PIN);
  }
else
  {
   GPIO_ResetBits(TST3_PIN_GPIO, TST3_PIN);
   GPIO_ResetBits(TST2_PIN_GPIO, TST2_PIN);
   ////GPIO_ResetBits(TST7_PIN_GPIO, TST7_PIN);
  }
#endif 
}
////========================================================================
void coolant_stop(void)
{
}
void coolant_init(void)
{
}
void coolant_sync(uint8_t mode)
{
}
void coolant_set_state(uint8_t mode)
{
}
uint8_t coolant_get_state()
{
return 0;
}
  
void  SetSpindleEnablebit(void)
{
}
void spindle_init(void)
{
}
void  ResetSpindleEnablebit(void)
{
}
void __spindle_set_state(uint8_t state)
  {
  }
void spindle_set_state(uint8_t state, float rpm)
  {
  }

void spindle_sync(uint8_t state, float rpm)
{
}

void spindle_stop()
{
}
uint8_t spindle_get_state()
{
return 0;
}
uint16_t spindle_compute_pwm_value(float rpm) // 328p PWM register is 8-bit.
{
  return 0;

}
void spindle_set_speed(uint16_t pwm_value)
  {
  }

////=====================================================
void  put_steps(uint8_t steps)////???
{
if(steps&(1 << X_STEP_BIT))
  {
  put_tst1_pin(0x1); 
////  printk("x");  
  }
else
  put_tst1_pin(0x0); 

if(steps&(1 << Y_STEP_BIT))
  {
//// printk("y");  
  put_tst2_pin(0x1); 
  }
else
  put_tst2_pin(0x0); 
if(steps&(1 << Z_STEP_BIT))
  {
  put_tst3_pin(0x1); 
//// printk("z");  
  }
else
  put_tst3_pin(0x0); 
         
}

void steps_reset(void)
{
  
}

void SetStepperDisableBit(void) ////GPIO_SetBits(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_MASK)
{
}

void ResetStepperDisableBit(void) ////GPIO_ResetBits(STEPPERS_DISABLE_PORT, STEPPERS_DISABLE_MASK)
{
}
