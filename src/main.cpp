#include "methods.h"
<<<<<<< Updated upstream
=======
#include "timer.h"
#include <math.h>
>>>>>>> Stashed changes

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
  switch (checkButton())      // ButtonPressed?
  {
  case BUTTON_SHORTPRESSED:
    break;

  case BUTTON_LONGPRESSED:
    break;

  default:
    break;
  }
<<<<<<< Updated upstream
=======
  if (timerAusgang)
  {
  static int average = 0;
  static int i = 0;
  average += analogData;
  i++;
  if (i > 23)
  {
    i = 0;
    average = average / 25;
    average = sqrt(average*250)-55;
    if(average < 0) {average = 0;}
    sendData(average);
    average = 0;
  }
  timerAusgang = 0;
  }
  //processData();

>>>>>>> Stashed changes
}
