#include "methods.h"
#include "timer.h"

const char *udpAddress = "192.168.4.255";
const int udpPort = 3333;
const char *ssid = "MPL";
const char *password = "123456789";

const int dataSize = 128;       //Größe eines Samples
int cutOff = 100;               //Wert, bis zu welcher Frequenz reagiert wird
int freqPerBin = 7;             //delta F pro Bin
short int data[dataSize] = {0}; //Array für Samples
int batteryTimer = 0;
int batteryLevel = 0;
int ledHight = 0;
bool dataFlag = 0;

char spectrum[dataSize / 2] = {0}; //Array für Spectrum

WiFiServer server(80);
WiFiUDP udp;

void init(void)
{
  Serial.begin(115200);
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  udp.begin(myIP, udpPort);
  server.begin();
  Serial.println("Server started");
  pinMode(BUTTONPIN, INPUT);
  pinMode(MICPIN, INPUT);
  pinMode(battery, INPUT);
  pinMode(timerPin, OUTPUT);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
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

void readMic(void)
{
  static int pos = 0; //Position im Datenarray
  static int avg = 0; //Mittelwert des gesampleten Signals

  if (pos < dataSize)
  {
    data[pos] = analogRead(MICPIN);
    avg += data[pos]; //alle Datenpunkte aufsummieren
    //Serial.println(data[pos]);
  }

  if (pos == dataSize)
  {

    avg = avg / dataSize; //Mittelwert des in data[] gespeicherten Signals berechnen
    for (int i = 0; i < dataSize; i++)
    {
      data[i] = (data[i] - avg) * 2; //Mittelwert von jedem Datenpunkt abziehen
    }

    pos = 0;
    dataFlag = 1;
  }
  pos++;
}

void processData(void)
{

  if (dataFlag)
  {
    static int cutOffBin = 0;         //Frequenzbin, bis zu welchem reagiert wird
    static short int maxFFTValue = 0; //maximalwert der FFT
    static float maxLedHight = 200;     //Maximaler Auschlag der Leds
    float currentLedHight = 0;        //Aktueller Auschlag der Leds
    const float numLed = 144;         //Anzahl der Leds
    static int counterH = 0;
    static int counterL = 0;
    static int counterAvg = 0;
    static int avg = 0;

    ZeroFFT(data, dataSize); //FFT berechnen

    cutOffBin = cutOff / freqPerBin;
    maxFFTValue = 0;

    for (int i = 2; i <= cutOffBin; i++)
    {
      if (maxFFTValue < data[i])
      {
        maxFFTValue = data[i];
      }
    }

    ledHight = maxFFTValue;
    //Serial.println(maxFFTValue);
    /*
    if (maxLedHight == 0)
    {
      maxLedHight = (currentLedHight * 1.2);
    }

    if (currentLedHight > maxLedHight * 0.8)
    {
      counterH++;
      if (counterH > 5000)
      {
        maxLedHight = (currentLedHight * 1.2);
        counterH = 0;
      }
    }

    if (currentLedHight < maxLedHight * 0.4)
    {
      counterL++;
      if (counterL > 5000)
      {
        maxLedHight = (currentLedHight * 1.2);
        counterL = 0;
      }
    }
    */

    ledHight = (int)(((ledHight / maxLedHight) * numLed) + 0.5);
    //Serial.println(ledHight);
    /*avg += ledHight;
    if (counterAvg == 1)
    {
      avg = avg / 2;
      sendData(avg);
      //Serial.println(avg);
      counterAvg = 0;
      avg = 0;
    }
    */
   sendData(ledHight);
    dataFlag = 0;
    counterAvg++;
  }
}

void readBattery(void)
{
  if (batteryTimer > 120000) //120 Sekunden warten
  {
    batteryLevel = analogRead(battery); //
    batteryTimer = 0;
  }
  batteryTimer++;

  if (batteryLevel < 1 && batteryTimer > 12345)
  {
    //--------------------------------------------------------
    
  }
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

void sendData(int value)
{
  udp.beginPacket(udpAddress, udpPort);
  udp.print(value);
  udp.endPacket();
}

void sendData(TargetClient target, Status status)
{
  udp.beginPacket(udpAddress, udpPort);
  udp.print(target);
  udp.print(status);
  udp.endPacket();
}

void sendData(TargetClient target, Status status, int value)
{
  udp.beginPacket(udpAddress, udpPort);
  udp.print(target);
  udp.print(status);
  udp.print(value);
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