#include <Arduino.h>
extern hw_timer_t *timer;
extern portMUX_TYPE timerMux;
extern int micData;
extern int timer1ms;

void IRAM_ATTR onTimer();