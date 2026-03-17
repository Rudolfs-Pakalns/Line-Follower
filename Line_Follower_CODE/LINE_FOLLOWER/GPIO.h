/**
 * @file GPIO.h
 * @author Rūdolfs Pakalns
 * @brief GPIO initialization library
 * @version 0.1
 * @date 2025-12-20
 */

#ifndef GPIO_H
#define GPIO_H

#define MOTOR_PIN_A1  5
#define MOTOR_PIN_A2  11
#define MOTOR_PIN_B1  9  // actual 10
#define MOTOR_PIN_B2  10 // actual 9
#define BUTTON        12
#define SENSOR_1      A0
#define SENSOR_2      A1
#define SENSOR_3      A2
#define SENSOR_4      A3
#define SENSOR_5      A4


void GPIO_Init(void);

#endif // GPIO_H




