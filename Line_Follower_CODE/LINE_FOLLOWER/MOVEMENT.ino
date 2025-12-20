/**
 * @file MOVEMENT.ino
 * @author Rūdolfs Pakalns
 * @brief movement control library
 * @version 0.1
 * @date 2025-12-20
 */


void Drive(uint8_t Pin_A1, uint8_t Pin_A2, uint8_t Pin_B1, uint8_t Pin_B2, uint8_t Speed)
{
  analogWrite(Pin_A1, Speed);
  analogWrite(Pin_A2, 0);

  analogWrite(Pin_B1, Speed);
  analogWrite(Pin_B2, 0);
}

