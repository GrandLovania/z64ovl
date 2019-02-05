#ifndef __Z64OVL_OOT_DEBUG_H__
#define __Z64OVL_OOT_DEBUG_H__

#define OOT_DEBUG 1

#include "mips.h"
#include "actor_oot.h"
#include "z64ovl.h"

// RAM Stuff
#define P1_CONTROLLER     0x80166AF0
#define P2_CONTROLLER     0x80166B08
#define P3_CONTROLLER     0x80166B20
#define P4_CONTROLLER     0x80166B38
#define RAM_SEGMENT_TABLE 0x80166FA8
#define GLOBAL_CONTEXT    0x80212020
#define VIEW_CONTEXT      0x802140F8
#define AS_A0             0x80213C44 // spawn_actor argument 0
#define OS_A0             0x802237C4 // spawn_object argument 0
#define LINK              0x802245B0
#define NAVI              0x8022CBE0
#define ZTARGETPOINTER    0x80213CEC

// Controller Buttons
#define INPUT_NONE        0b0000000000000000
#define INPUT_C_RIGHT     0b0000000000000001
#define INPUT_C_LEFT      0b0000000000000010
#define INPUT_C_DOWN      0b0000000000000100
#define INPUT_C_UP        0b0000000000001000
#define INPUT_R_TRIGGER   0b0000000000010000
#define INPUT_L_TRIGGER   0b0000000000100000
#define INPUT_D_RIGHT     0b0000000100000000
#define INPUT_D_LEFT      0b0000001000000000
#define INPUT_D_DOWN      0b0000010000000000
#define INPUT_D_UP        0b0000100000000000
#define INPUT_START       0b0001000000000000
#define INPUT_Z           0b0010000000000000
#define INPUT_B           0b0100000000000000
#define INPUT_A           0b1000000000000000

enum DISP{
	WORK = 0x01BC,
	OVERLAY = 0x02B0,
	POLY_OPA = 0x02C0,
	POLY_XLU = 0x02D0
};

#endif
