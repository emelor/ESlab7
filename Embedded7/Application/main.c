#include <basic/bs_basic.h>
#include <hal.h>
#include <ros_xhp.h>
#include <blue/b_thread.h>
#include "r_ex_r.h"


uint32_t rubusIdleLoop;
int_t stackRedUsed;
int_t stackBlueUsed;

void rubusIdleMain(void)
{
	rubusIdleLoop = 0;
	for (;;)
	{
		rubusIdleLoop++;
			if (redStackUsed(&stackRedUsed) != R_OK)
			{
				halHalt();
			}
			if (blueStackUsed(&stackBlueUsed) != R_OK)
			{
				halHalt();
			}
			SIM_BLUE_IDLE
	}
}


void main(void)
{
if (halInit() != R_OK)
	halHalt();
if (bsRubusInit() != R_OK)
	halHalt();
if (halStart() != R_OK)
	halHalt();
bsRubusStart();
}