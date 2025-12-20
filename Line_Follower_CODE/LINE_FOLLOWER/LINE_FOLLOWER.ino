/**
 * @file LINE_FOLLOWER.ino
 * @author Rūdolfs Pakalns
 * @brief Main code for line follower robot using PID control
 * @version 0.1
 * @date 2025-12-20
 */

// Includes
#include "GPIO.h"
#include "MOVEMENTS.h"
// Definitions
#define ARRAY_SIZE 5

// PV
uint8_t sensors[ARRAY_SIZE] = {0};
int8_t weights[ARRAY_SIZE] = {-2, -1, 0, 1, 2 };
int8_t error = 0;
uint8_t PID = 0;
uint8_t speed = 0;

// PFP
int8_t calculate_error(uint8_t *sensors, int8_t *weights);

void setup() 
{
  Serial.begin(9600);
  GPIO_Init();
}

void loop() 
{
  error = calculate_error(sensors, weights);

  // DO SOMETHING TO CONVERT ERROR INTO SPEED FOR MOTORS
    
  Drive(MOTOR_PIN_A1, MOTOR_PIN_A2, MOTOR_PIN_B1, MOTOR_PIN_B2, speed);

}


/**
 * @brief Calculate the weighted error from sensor readings
 * 
 * @param sensors Array of sensor readings (0 or 1)
 * @param weights Array of weights corresponding to each sensor
 * @return int8_t Calculated error value
 */
int8_t calculate_error(uint8_t *sensors, int8_t *weights)
{
  int8_t weighted_sum = 0;
  int8_t sensor_sum = 0;

  for (uint8_t i = 0; i < ARRAY_SIZE; i++)
  {
    weighted_sum += sensors[i] * weights[i];
    sensor_sum += sensors[i];
  }

  if (sensor_sum == 0) return 0; 
  

  return weighted_sum / sensor_sum;
}
