#include <WiFi.h>
#include <Arduino.h>
//#include <WiFiUdp.h>

#define longPress 2000
#define shortPress 100
#define BUTTONPIN 25
#define MICPIN 35       // only ADC1 can be used with WIFI
#define SAMPLINGRATE 10 // 10ms
#define LOWLEVEL 10
#define AVERAGETIME 25

extern const char *udpAddress;
extern const int udpPort;
extern const char *ssid;
extern const char *password;
extern long micData;

extern WiFiServer server;
extern WiFiUDP udp;
extern WiFiClient client;

enum TargetClient
{
    CLIENT_BASESTATION,
    CLIENT_LIGHTTOWER_1,
    CLIENT_LIGHTTOWER_2,
    CLIENT_ALL_LIGHTTOWER,
    CLIENT_NONE,
};

enum Status
{
    STATUS_MUSIC,
    STATUS_OFF,
    STATUS_COLOR,
    STATUS_NONE,
};

enum ButtonStates
{
    BUTTON_LONGPRESSED,
    BUTTON_SHORTPRESSED,
    BUTTON_UNKNOWN,
};


void handleWiFiClient(void);
ButtonStates checkButton(void);
void readMic(void);
void init(void);

void sendData(int data);
void sendData(TargetClient target, Status status);
void sendData(TargetClient target, Status status, unsigned int red, unsigned int green, unsigned int blue);