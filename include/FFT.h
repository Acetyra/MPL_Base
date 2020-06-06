#include <Adafruit_ZeroFFT.h>
#include "fix_fft.h"
#include "webServerDIY.h"

#define DATASIZE 128
#define CUTOFFFREQ 150
#define SAMPLINGFREQ 2000
#define NUMLEDS 144
#define FREQPERBIN ((int)((float)SAMPLINGFREQ/(float)DATASIZE))

void processData(short int data[]);