#include "Arduino.h"
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "GPIO.h"


void Drive(uint8_t Pin_A1, uint8_t Pin_A2, uint8_t Pin_B1, uint8_t Pin_B2, uint8_t Speed)
{
  analogWrite(Pin_A1, Speed);
  analogWrite(Pin_A2, 0);

  analogWrite(Pin_B1, Speed);
  analogWrite(Pin_B2, 0);
}

#endif // MOVEMENT_H