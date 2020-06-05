#include <Arduino.h>
extern hw_timer_t *timer;
extern portMUX_TYPE timerMux;
extern int analogData;
extern int timerAusgang;

void IRAM_ATTR onTimer();