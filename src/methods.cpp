#include "methods.h"

const char *udpAddress = "192.168.4.255";
const int udpPort = 3333;

WiFiServer server(80);
WiFiUDP udp;

void checkButton(void)
{
  static unsigned long mill = 0;
  static unsigned int buttonPressed = 0;
  if (!digitalRead(BUTTONPIN) && (mill != millis()))
  { // button pressed and at least 1ms passed
    buttonPressed++;
    mill = millis();
    //Serial.println(buttonPressed);
  }
  if (digitalRead(BUTTONPIN) && buttonPressed)
  { // button released
    if (buttonPressed >= longPress)
    { // button was long pressed
      Serial.println("long pressed");
    }
    else if (buttonPressed >= shortPress)
    { // button was short pressed
      Serial.println("short pressed");
    }
    else
    {
    }
    buttonPressed = 0;
  }
}

long readMic(void)
{
  static unsigned long mill = millis();
  if (millis() - mill > SAMPLINGRATE) // check if at least SAMPLINGRATE ms has passed
  {
    mill = millis();
    int analog = analogRead(MICPIN); // read analog value
    //Serial.println(analog);
    if (analog > LOWLEVEL)
    {
      return analogRead(analog);
    }
    else
    {
      return 0;
    }
  }
  return -1;
}

void handleWiFiClient(void)
{
  Serial.println("New Client."); // print a message out the serial port
  String currentLine = "";       // make a String to hold incoming data from the client
  while (client.connected())
  { // loop while the client's connected
    if (client.available())
    {                         // if there's bytes to read from the client,
      char c = client.read(); // read a byte, then
      //Serial.write(c);                  // print it out the serial monitor
      if (c == '\n')
      { // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0)
        {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println(); // Don't delete this line!
          client.println("<!DOCTYPE html><html><head>");
          client.println("<style>");
          // CSS Section to set styles check out W3C School for help
          client.println("body    {background-color: lightblue;font-family: tahoma;}");
          client.println("h1      {color: red;text-align: center;}");
          client.println("p       {font-size: 20px;text-align: center;colour:MediumOrchid}");
          client.println(".button {background-color:blue;color:white;padding:10px 32px;text-align:center;text-decoration:none;display:inline-block;");
          client.println("font-size:16px;margin: 4px 2px;cursor: pointer;width:8%;}");
          client.println("</style>");
          client.println("</head><body>");
          client.println("<h1>MPL - Mobile Party Light</h1>");
          client.println("<p>Select Client Device to control</p>");
          // the content of the HTTP response follows the header:
          client.print("<div style = \"text-align: center;\">");
          // Controls for sending a Turn-ON message
          client.print("<a class=\"button\" href=\"/C01H\">Client 1 Device ON</a>");
          client.print("<a class=\"button\" href=\"/C01L\">Client 1 Device OFF</a>");
          //client.print("<a class=\"button\" href=\"/C01L\">Client 1 Device OFF</a>");
          client.print("<br>"); // New line
          // Controls for sending a Turn-OFF message
          client.print("<a class=\"button\" href=\"/C02H\">Client 2 Device ON</a>");
          client.print("<a class=\"button\" href=\"/C02L\">Client 2 Device OFF</a>");
          //client.print("<a class=\"button\" href=\"/C02L\">Client 2 Device OFF</a>");
          client.print("<br>"); // New line
          // Controls for sending a general or broadcast like message
          client.print("<a class=\"button\" href=\"/CAON\">Turn All Client Devices ON</a>");
          client.print("<a class=\"button\" href=\"/CAOFF\">Turn All Client Devices OFF</a>");
          client.print("</div>");
          // The HTTP response ends with another blank line:
          client.println();
          client.println("</body></html>");
          // break out of the while loop:
          break;
        }
        else
        { // if you got a newline, then clear currentLine:
          currentLine = "";
        }
      }
      else if (c != '\r')
      {                   // if you got anything else but a carriage return character,
        currentLine += c; // add it to the end of the currentLine
      }
      
      /***** Client-01 High *****/
      if (currentLine.endsWith("GET /C01H"))
      {
        sendData(CLIENT_LIGHTTOWER_1, STATUS_COLOR);
      } 

      /***** Client-02 High *****/
      if (currentLine.endsWith("GET /C02H"))
      {
        sendData(CLIENT_LIGHTTOWER_2, STATUS_COLOR);
      } 

      /***** Client-01 Low *****/
      if (currentLine.endsWith("GET /C01L"))
      {
        sendData(CLIENT_LIGHTTOWER_1, STATUS_OFF);
      }

      /***** Client-02 Low *****/
      if (currentLine.endsWith("GET /C02L"))
      {
        sendData(CLIENT_LIGHTTOWER_2, STATUS_OFF);
      }

      /***** All Clients High *****/
      if (currentLine.endsWith("GET /CAON"))
      {
        sendData(CLIENT_ALL_LIGHTTOWER, STATUS_MUSIC);
      }

      /***** All Clients Low *****/
      if (currentLine.endsWith("GET /CAOFF"))
      {
        sendData(CLIENT_ALL_LIGHTTOWER, STATUS_OFF);
      }
    }
  }
  // close the connection:
  client.stop();
  Serial.println("Client Disconnected.");
}

void sendData(TargetClient target, Status status)
{
  udp.beginPacket(udpAddress, udpPort);
  udp.print(target);
  udp.print(status);
  udp.endPacket();
}

void sendData(TargetClient target, Status status, unsigned int red, unsigned int green, unsigned int blue)
{
  udp.beginPacket(udpAddress, udpPort);
  udp.print(target);
  udp.print(status);
  udp.print(red);
  udp.print(green);
  udp.print(blue);
  udp.endPacket();
}