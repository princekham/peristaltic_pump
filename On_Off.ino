#include <Arduino_FreeRTOS.h>
void TaskBlink1( void *pvParameters );
void Taskprint( void *pvParameters );
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  xTaskCreate(
    TaskBlink1
    ,  "task1"   
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
    xTaskCreate(
    Taskprint
    ,  "task3"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
vTaskStartScheduler();
}
void loop()
{
}
void TaskBlink1(void *pvParameters)  {
  pinMode(8, OUTPUT);
  while(1)
  {
    Serial.println("Task1");
    digitalWrite(8, HIGH);   
    vTaskDelay( 60000 / portTICK_PERIOD_MS ); // one minute on 3 mins off.
    digitalWrite(8, LOW);    
    vTaskDelay( 150000 / portTICK_PERIOD_MS ); 
  }
}

void Taskprint(void *pvParameters)  {
  int counter = 0;
  while(1)
  {
counter++;
  Serial.println(counter); 
  vTaskDelay(2000 / portTICK_PERIOD_MS);    }
}
