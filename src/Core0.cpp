#include "Core0.h"


void readMic(void);
ButtonStates checkButton(void);
void readBattery(void);


bool sendDataFlag = false;
unsigned int batteryLevel = 0;

void Task1code(void *pvParameters)
{
  for (;;)
  {
  
    // listen for incoming clients
    if (getServerAvailable()) // if you get a client
    {
      handleWiFiClient();
    }
    readBattery();
    switch (checkButton()) // ButtonPressed?
    {
    case BUTTON_SHORTPRESSED:
      break;

    case BUTTON_LONGPRESSED:
      break;

    default:
      break;
    }
    if (readMicFlag)
    {
      //Serial.println("READING MIC");
      readMic();
      readMicFlag = false;
    }
    if (sendDataFlag)
    {
      sendData(ledHight);
      sendDataFlag = 0;
    }
  }
}

void readMic(void)
{
  static int pos = 0;                       //Position im Datenarray
  static int avg = 0;                       //Mittelwert des gesampleten Signals
  static short int samples[DATASIZE] = {0}; //Array für Samples

  if (pos < DATASIZE)
  {
    samples[pos] = analogRead(MICPIN);
    avg += samples[pos]; //alle Datenpunkte aufsummieren
    //Serial.println(data[pos]);
  }

  if (pos == DATASIZE)
  {

    avg = avg / DATASIZE; //Mittelwert des in data[] gespeicherten Signals berechnen
    for (int i = 0; i < DATASIZE; i++)
    {
      data[i] = (samples[i] - avg) * 2; //Mittelwert von jedem Datenpunkt abziehen
    }

    pos = 0;
    dataFlag = 1;
  }
  pos++;
}

void readBattery(void)
{
  if (readBatteryFlag > 120000) //120 Sekunden warten
  {
    batteryLevel = analogRead(BATTERYPIN); //
    readBatteryFlag = 0;
  }
  if (batteryLevel < 1 && readBatteryFlag > 12345)
  {
    //--------------------------------------------------------
  }
}

ButtonStates checkButton(void)
{
  static unsigned long mill = 0;
  static unsigned int buttonPressed = 0;
  ButtonStates tmp = BUTTON_UNKNOWN;

  // button pressed and at least 1ms passed
  if (!digitalRead(BUTTONPIN) && (mill != millis()))
  {
    buttonPressed++;
    mill = millis();
    //Serial.println(buttonPressed);
  }

  // Button released after being pressed
  if (digitalRead(BUTTONPIN) && buttonPressed)
  {
    buttonPressed = 0;
    // Button was long pressed
    if (buttonPressed >= longPress)
    {
      Serial.println("long pressed");
      tmp = BUTTON_LONGPRESSED;
    }

    // Button was short pressed
    else if (buttonPressed >= shortPress)
    {
      Serial.println("short pressed");
      tmp = BUTTON_SHORTPRESSED;
    }
  }
  return tmp;
}