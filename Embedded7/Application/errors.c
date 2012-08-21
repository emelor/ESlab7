#include <basic/bs_basic.h>
#include <blue/b_thread.h>
#include <green/g_thread.h>
#include <red/r_thread.h>
#include <r_ex_r.h>
#include <hal.h>

int_t errorCode;
bsObject_t const *errorObject;
void blueError (int_t code, bsObject_t const
*object)
{
errorCode = code;
errorObject = object;
halHalt();
}
void greenError (int_t code,bsObject_t const
*object)
{
errorCode = code;
errorObject = object;
halHalt();
}
void redError (int_t code,bsObject_t const *object)
{
errorCode = code;
errorObject = object;
if (code != R_ERROR_DEADLINE_OVERRUN) {
halHalt();
}
redSetScheduleImmediate(&redScheduleStart);
}