/**
 * @file MOVEMENT.h
 * @author Rūdolfs Pakalns
 * @brief movement control library
 * @version 0.1
 * @date 2025-12-20
 */


void Right_Motor_Forward(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed);
void Right_Motor_Reverse(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed);
void Left_Motor_Forward(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed);
void Left_Motor_Reverse(uint8_t Pin_1, uint8_t Pin_2, uint8_t Speed);
void Stop_Motors(void);