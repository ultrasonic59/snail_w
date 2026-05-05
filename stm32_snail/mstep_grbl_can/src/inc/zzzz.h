#ifndef __ZZZZ_H__
#define __ZZZZ_H__
#include <stdint.h>
#include "settings.h"

///=======================================================================
extern settings_t settings;

extern uint32_t HAL_GetTick(void);
extern void settings_init() ;
extern void stepper_init();
extern void system_init();
extern void serial_reset_read_buffer();
extern void gc_init();

extern void spindle_init();
extern void coolant_init();
extern void limits_init();
extern void probe_init();
extern void plan_reset(); // Clear block buffer and planner variables
extern void st_reset(); // Clear stepper subsystem variables.

	    // Sync cleared gcode and planner positions to current system position.
extern void plan_sync_position();
extern void gc_sync_position();

extern void report_init_message();

	    // Start Grbl main loop. Processes program inputs and executes them.
extern void protocol_main_loop();

#endif ////  __ZZZZ_H__ 
