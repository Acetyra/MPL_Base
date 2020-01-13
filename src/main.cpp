#include "methods.h"

const char *ssid = "MPL";
const char *password = "123456789";

unsigned int mill = 0;

WiFiClient client;

void setup()
{
  // put your setup code here, to run once:
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
