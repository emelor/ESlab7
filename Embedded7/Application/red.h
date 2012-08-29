



#ifndef _RED_H_
#define _RED_H_
void redStartMain(void);
void blinky0Main (int *state);
void blinky1Main (int *state);
void blinky2Main (int *state);
void blinky3Main (int *state);
typedef struct {
int counter;
int schedule;
} blinkyModeType;
void blinkyReschedMain (blinkyModeType *state);
#endif