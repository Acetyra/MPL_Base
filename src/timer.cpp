#include "timer.h"
#include "methods.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
int timer1ms = 0;
int micData = 0;

void IRAM_ATTR onTimer() 
{
    portENTER_CRITICAL_ISR(&timerMux);

    micData = readMic();
    timer1ms++;
    portEXIT_CRITICAL_ISR(&timerMux);
}