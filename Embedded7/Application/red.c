#include <r_ex_bs.h>
#include <hal.h>
#include <r_ex_r.h>
#include "red.h"
#include <LEDDriver.h>


void redStartMain(void) {
leds_initialise();
blinky0Args = 0;
redSetSchedule(&redScheduleBlinky0);
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