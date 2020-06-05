#include "timer.h"
#include "methods.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
bool timerAusgang = 0;


void IRAM_ATTR onTimer() 
{
    portENTER_CRITICAL_ISR(&timerMux);
    timerAusgang = 1;
    readMic();
    //readBattery();
    //timerausgang = !timerausgang;
    //digitalWrite(timerPin, timerausgang);

    portEXIT_CRITICAL_ISR(&timerMux);
}