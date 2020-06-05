#include "timer.h"
#include "methods.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
int timerAusgang = 0;
int analogData = 0;

void IRAM_ATTR onTimer() 
{
    portENTER_CRITICAL_ISR(&timerMux);

    analogData = readMic();
    timerAusgang++;
    //readBattery();
    //timerausgang = !timerausgang;
    //digitalWrite(timerPin, timerausgang);

    portEXIT_CRITICAL_ISR(&timerMux);
}