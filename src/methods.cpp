
#include "methods.h"



int batteryTimer = 0;
int batteryLevel = 0;
int ledHight = 0;
bool dataFlag = 0;
short int data[DATASIZE] = {0}; //Array für Samples


TaskHandle_t Task1;
TaskHandle_t Task2;

void initCores(void)
{
  // Core 0
  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */

  //Core 1
  xTaskCreatePinnedToCore(
      Task2code, /* Task function. */
      "Task2",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task2,    /* Task handle to keep track of created task */
      1);        /* pin task to core 1 */
}

void initTimer(void)
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
}

void init(void)
{
  Serial.begin(115200);
  Serial.println("Configuring access point...");
  initWiFi();
  initCores();
  initTimer();
  pinMode(BUTTONPIN, INPUT);
  pinMode(MICPIN, INPUT);
  pinMode(battery, INPUT);
  pinMode(timerPin, OUTPUT);


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

  if (pos < DATASIZE)
  {
    data[pos] = analogRead(MICPIN);
    avg += data[pos]; //alle Datenpunkte aufsummieren
    //Serial.println(data[pos]);
  }

  if (pos == DATASIZE)
  {

    avg = avg / DATASIZE; //Mittelwert des in data[] gespeicherten Signals berechnen
    for (int i = 0; i < DATASIZE; i++)
    {
      data[i] = (data[i] - avg) * 2; //Mittelwert von jedem Datenpunkt abziehen
    }

    pos = 0;
    dataFlag = 1;
  }
  pos++;
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
