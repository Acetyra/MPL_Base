#include "main.h"

void initCores(void);

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Configuring access point...");
  //esp_task_wdt_init(2, false);
  initTimer();
  disableCore0WDT();
  disableCore1WDT();
  disableLoopWDT();
  initWiFi();
  initCores();
  pinMode(BUTTONPIN, INPUT);
  pinMode(MICPIN, INPUT);
  pinMode(BATTERYPIN, INPUT);

}

void loop()
{
  // put your main code here, to run repeatedly:
}

void initCores(void)
{
  // Core 0
  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      5,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */

  //Core 1
  xTaskCreatePinnedToCore(
      Task2code, /* Task function. */
      "Task2",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      5,         /* priority of the task */
      &Task2,    /* Task handle to keep track of created task */
      1);        /* pin task to core 1 */
}
