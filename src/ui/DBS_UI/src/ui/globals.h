#ifndef GLOBALS_H
#define GLOBALS_H

#include <lvgl/lvgl.h>
#include "types.h"

extern char userAccountNumber[32];
extern char accountNumber[32];
extern char amount[32];
extern char pin[32];

extern int currentFingerId;
extern User* currentUser;

extern volatile int billPulseCount;
extern volatile int billDetected; 
extern double billValue;

#endif
