#include <Arduino.h>
#include "methods.h"

extern hw_timer_t *timer;
extern portMUX_TYPE timerMux;

void IRAM_ATTR onTimer();