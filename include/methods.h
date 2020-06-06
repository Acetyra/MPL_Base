#ifndef METHODS_H
#define METHODS_H

#include "webServerDIY.h"
#include "timer.h"
#include <Core0.h>
#include <Core1.h>
#include "FFT.h"
#include <WiFi.h>
#include <Arduino.h>
#include "webServerDIY.h"


//#include <WiFiUdp.h>

#define longPress 2000
#define shortPress 100
#define BUTTONPIN 25
#define MICPIN 35       // only ADC1 can be used with WIFI
#define timerPin 33
#define SAMPLINGRATE 10 // 10ms
#define LOWLEVEL 10
#define battery 34

#endif /* METHODS_H */


void handleWiFiClient(void);
ButtonStates checkButton(void);
void readMic(void);
void processData(void);
void readBattery(void);
void init(void);
