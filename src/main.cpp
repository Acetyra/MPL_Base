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

  if (timer1ms)
  {
    static int average = 0;
    static int i = 0;
    average += micData;
    i++;
    if (i > AVERAGETIME - 2)
    {
      average /= AVERAGETIME;
      average = sqrt(average * 250) - 55;
      if (average < 0)
      {
        average = 0;
      }
      else if (average > 144)
      {
        average = 144;
      }
      sendData(average);
      average = 0;
      i = 0;
    }
    timer1ms = 0;
  }
}
