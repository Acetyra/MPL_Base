#ifndef WEBSERVERDIY_H
#define WEBSERVERDIY_H

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
#endif /* WEBSERVERDIY_H */


void initWiFi(void);
bool getServerAvailable(void);
void handleWiFiClient(void);
void sendData(int value);
void sendData(TargetClient target, Status status);
void sendData(TargetClient target, Status status, int value);
void sendData(TargetClient target, Status status, unsigned int red, unsigned int green, unsigned int blue);
