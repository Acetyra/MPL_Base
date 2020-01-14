#include "methods.h"



unsigned int mill = 0;

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
  if (client)                             // if you get a client
  {
    handleWiFiClient();   
  }
}
