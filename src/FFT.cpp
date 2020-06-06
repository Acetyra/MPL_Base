#include "FFT.h"

short int data[DATASIZE] = {0}; //Array für Samples
int ledHight;

void processData(void)
{
    static int cutOffBin = 0;         //Frequenzbin, bis zu welchem reagiert wird
    static short int maxFFTValue = 0; //maximalwert der FFT
    //Serial.println("Data wird geprocessed");
    static float maxLedHight = 200; //Maximaler Auschlag der Leds

    ZeroFFT(data, DATASIZE); //FFT berechnen

    cutOffBin = CUTOFFFREQ / FREQPERBIN;
    maxFFTValue = 0;

    for (int i = 2; i <= cutOffBin; i++)
    {
        if (maxFFTValue < data[i])
        {
            maxFFTValue = data[i];
        }
    }

    ledHight = maxFFTValue;

    ledHight = (int)(((ledHight / maxLedHight) * NUMLEDS) + 0.5);
    sendDataFlag = true;
}