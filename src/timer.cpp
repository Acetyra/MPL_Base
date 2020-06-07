#include "timer.h"


hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
bool readMicFlag = false;
unsigned int readBatteryFlag = 0;

void initTimer(void)
{
  timer = timerBegin(0, 8, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
}

void IRAM_ATTR onTimer() 
{
    portENTER_CRITICAL_ISR(&timerMux);
    readMicFlag = true;
    readBatteryFlag++;
    portEXIT_CRITICAL_ISR(&timerMux);
}