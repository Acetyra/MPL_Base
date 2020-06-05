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
    average += (((double)micData / 2048.0) * 144.0);
    i++;
    if (i > 23)
    {
      average = average / 25;
      average = sqrt(average * 250) - 55;
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
