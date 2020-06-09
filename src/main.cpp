#include "methods.h"
#include "timer.h"
#include <math.h>

WiFiClient client;


void setup()
{
  // put your setup code here, to run once:
  init();
}
//PENIS
void loop()
{
  // put your main code here, to run repeatedly:
  client = server.available(); // listen for incoming clients
  if (client)                  // if you get a client
  {
    handleWiFiClient();
  }
  switch (checkButton()) // ButtonPressed?
  {
  case BUTTON_SHORTPRESSED:
    break;

  case BUTTON_LONGPRESSED:
    break;
  }

  if (timerAusgang)
  {
    static double average = 0;
    static int i = 0;
    static int maxValue = 0;
    static int minValue = 144;
    if (micData < minValue)
    {
      minValue = micData;
    }
    else if (micData > maxValue)
    {
      maxValue = micData;
    }
    average += (((double)micData / 2048.0) * 144.0);
    i++;
    if (i > 98)
    {
      average = average / 100;
      //average = sqrt(average * 400) - 57 - (average/3);
      if (average < 0)
      {
        average = 0;
      }
      else if (average > 144)
      {
        average = 144;
      }
      //Serial.println(average);
      sendData((int)average);
      average = 0;
      i = 0;
    }
    timerAusgang = 0;
  }
}
