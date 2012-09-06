#include <r_ex_bs.h>
#include <hal.h>
#include <r_ex_r.h>
#include "red.h"
#include <LEDDriver.h>
#include "support_common.h"
#include <stdio.h>


void redStartMain(void) {
leds_initialise();
blinkyReschedArgs.counter = 0;
blinkyReschedArgs.schedule = 1;
blinky0Args = 0;
blinky1Args = 0;
blinky2Args = 0;
blinky3Args = 0;
redSetSchedule(&redScheduleBlinky0);
//redSetSchedule(&redSchedule2);
}





void blinkyReschedMain (blinkyModeType *state)
{
(state->counter)++;
if (state->counter == 10) {
state->counter = 0;
state->schedule = 3 - state->schedule; //switch
switch (state->schedule) {
case 1:
redSetSchedule(&redScheduleBlinky0);
break;
case 2:
redSetSchedule(&redSchedule2);
break;
default:
halExit(); break;
}
}
}

void blinky0Main (int *state) {
printf("hej");
if (*state == 0) {
*state = 1;
leds_turnON(0);
}
else {
*state = 0;
leds_turnOFF(0);
}
}


void blinky1Main (int *state) {
if (*state == 0) {
*state = 1;
leds_turnON(1);
}
else {
*state = 0;
leds_turnOFF(1);
}
}


void blinky2Main (int *state) {
if (*state == 0) {
*state = 1;
leds_turnON(2);
}
else {
*state = 0;
leds_turnOFF(2);
}
}


void blinky3Main (int *state) {
if (*state == 0) {
*state = 1;
leds_turnON(3);
}
else {
*state = 0;
leds_turnOFF(3);
}
}