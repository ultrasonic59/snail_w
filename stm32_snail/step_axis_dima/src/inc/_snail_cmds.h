#ifndef __SNAIL_CMDS_H__
#define __SNAIL_CMDS_H__
////========X ===========================  
#define STOP_X          0x10
#define GOTO_X          0x11
#define SET_SPD_X       0x12
////========Y ===========================  
#define STOP_Y          0x20
#define GOTO_Y          0x21
#define SET_SPD_Y       0x22
////========Z ===========================  
#define STOP_Z          0x30
#define GOTO_Z          0x31
#define SET_SPD_Z       0x32
////======================================
////============= CAN ====================
#define SET_STOP_ALL    0x10             ////Avaria
#define SET_STOP        0x11             ///
#define GET_STATE       0x12             ////
#define SET_HOME        0x13             ////

#define SET_STEP_X     0x20             ////set step,speed,dir X
#define SET_STEP_Y     0x40             ////set step,speed,dir Y
#define SET_STEP_Z     0x80             ////set step,speed,dir Z
#define PUT_STATE_X    0x100             ////
#define PUT_STATE_Y    0x101             ////
#define PUT_STATE_Z    0x102             ////

////======================================
typedef struct step_cmd_s_
{
uint16_t steps;
uint16_t b_speed;
uint16_t e_speed;
uint16_t flags;
}step_cmd_t;


#endif