#include <Arduino.h>
#include "main.h"

extern bool readMicFlag;
extern unsigned int readBatteryFlag;

extern void initTimer();
void IRAM_ATTR onTimer();