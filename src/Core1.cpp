#include "Core1.h"

bool dataFlag = false;

void Task2code(void *pvParameters)
{
    for (;;)
    {
        Serial.println("ich lebe");
        if (dataFlag)
        {
            Serial.println("data processing");
            processData();
            dataFlag = false;
        }
    }
}