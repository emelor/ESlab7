#include <basic/bs_basic.h>
#include <blue/b_thread.h>
#include <green/g_thread.h>
#include <red/r_thread.h>
#include <r_ex_r.h>
#include <hal.h>
#include "support_common.h"
#include <stdio.h>
#include "ros_services.h"




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
printf("RED ERROR %d in %s\n\r", code,bsObjectName(object->index));
errorCode = code;
errorObject = object;
if (code != R_ERROR_DEADLINE_OVERRUN) {
halHalt();
}
redSetScheduleImmediate(&redScheduleStart);
}