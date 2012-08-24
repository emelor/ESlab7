#include <r_ex_bs.h>
#include <hal.h>
#include <r_ex_r.h>
#include "red.h"
#include <LEDDriver.h>


void redStartMain(void) {
leds_initialise();
blinky0Args = 0;
blinky1Args = 0;
blinky2Args = 0;
blinky3Args = 0;
//redSetSchedule(&redScheduleBlinky0);
redSetSchedule(&redSchedule2);
}

void blinky0Main (int *state) {
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