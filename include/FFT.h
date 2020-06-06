#include <Adafruit_ZeroFFT.h>
#include "fix_fft.h"
#include "webServerDIY.h"
#include "main.h"

#define DATASIZE 128
#define CUTOFFFREQ 150
#define SAMPLINGFREQ 2000
#define NUMLEDS 144
#define FREQPERBIN ((int)((float)SAMPLINGFREQ/(float)DATASIZE))

extern short int data[DATASIZE];
extern int ledHight;
void processData(void);