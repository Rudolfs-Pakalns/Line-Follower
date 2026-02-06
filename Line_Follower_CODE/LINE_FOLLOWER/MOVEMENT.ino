/**
 * @file MOVEMENT.ino
 * @author Rūdolfs Pakalns
 * @brief movement control library
 * @version 0.1
 * @date 2025-12-20
 */


void Right_Motor_Forward(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed)
{
  analogWrite(Pin_1, Speed);
  analogWrite(Pin_2, 0);
}

void Right_Motor_Reverse(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed)
{
  analogWrite(Pin_1, 0);
  analogWrite(Pin_2, Speed);
}

void Left_Motor_Forward(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed)
{
  analogWrite(Pin_1, Speed);
  analogWrite(Pin_2, 0);
}

void Left_Motor_Reverse(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed)
{
  analogWrite(Pin_1, 0);
  analogWrite(Pin_2, Speed);
}


