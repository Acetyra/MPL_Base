#include "Core0.h"



void Task1code(void *pvParameters)
{
    for (;;)
    {
        // listen for incoming clients
        if (getServerAvailable()) // if you get a client
        {
            handleWiFiClient();
        }

        switch (checkButton()) // ButtonPressed?
        {
        case BUTTON_SHORTPRESSED:
            break;

        case BUTTON_LONGPRESSED:
            break;

        default:
            break;
        }
    }
}