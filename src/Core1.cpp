#include "Core1.h"

bool dataFlag = false;

void Task2code(void *pvParameters)
{
    for (;;)
    {
        yield();
        if (dataFlag)
        {
            processData();
            dataFlag = false;
        }
    }
}