#include "methods.h"
#include "timer.h"

WiFiClient client;

void setup()
{
  // put your setup code here, to run once:
  init();
}

void loop()
{
  // put your main code here, to run repeatedly:
  client = server.available(); // listen for incoming clients
  if (client)                  // if you get a client
  {
    handleWiFiClient();
  }
  switch (checkButton())      // ButtonPressed?
  {
  case BUTTON_SHORTPRESSED:
    break;

  case BUTTON_LONGPRESSED:
    break;

  default:
    break;
  }

  processData();

}
