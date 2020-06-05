#include <Arduino.h>
extern hw_timer_t *timer;
extern portMUX_TYPE timerMux;
extern bool timerAusgang;

void IRAM_ATTR onTimer();