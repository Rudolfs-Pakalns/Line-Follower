/**
* 
*
*/
#include "GPIO.h"
#include "MOVEMENT.h"

void setup() 
{
  Serial.begin(9600);
  GPIO_Init();

}

void loop() 
{
  
  Drive(MOTOR_PIN_A1, MOTOR_PIN_A2, MOTOR_PIN_B1, MOTOR_PIN_B2, 100);

}
