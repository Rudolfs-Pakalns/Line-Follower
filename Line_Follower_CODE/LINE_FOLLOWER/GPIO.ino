/**
 * @file GPIO.ino
 * @author Rūdolfs Pakalns
 * @brief GPIO initialization library
 * @version 0.1
 * @date 2025-12-20
 */


/**
 * @brief Initialize GPIO pins
 */
void GPIO_Init(void)
{
  pinMode(MOTOR_PIN_A1 | MOTOR_PIN_A2 | MOTOR_PIN_B1 | MOTOR_PIN_B2, OUTPUT);
  pinMode(SENSOR_1 | SENSOR_2 | SENSOR_3 | SENSOR_4 | SENSOR_5, INPUT);
  pinMode(BUTTON, INPUT);
}
