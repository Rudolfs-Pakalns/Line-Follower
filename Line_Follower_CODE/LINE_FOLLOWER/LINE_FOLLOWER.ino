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
#define BASE_SPEED 100

// PV
uint8_t   sensors[ARRAY_SIZE] = {SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5};
uint8_t   sensor_reads[ARRAY_SIZE] = {0};
int8_t    weights[ARRAY_SIZE] = {-2, -1, 0, 1, 2 };
int8_t    error = 0;

int16_t P = 0;
int16_t I = 0;
int16_t D = 0;
float kP = 25.0;
float kI = 2.0;
float kD = 15.0;
uint8_t   speed = 0;
int8_t   last_error = 0;

// PFP
int8_t calculate_error(uint8_t *sensor_reads, int8_t *weights);
void handleBT();
void Read_Sensors(uint8_t *sensor_array, uint8_t *sensor_reads);

// Main code
void setup() 
{
  Serial.begin(9600);
  GPIO_Init();
}

// Main loop
void loop() 
{
  handleBT();

  Read_Sensors(sensors, sensor_reads);

  error = calculate_error(sensor_reads, weights);

  P = error;
  I += error; I = constrain(I, -50, 50); 
  D = error - last_error;
  
  
  // Serial.print("Error: "); Serial.print(error);
  // Serial.print(" kP: "); Serial.print(kP);
  // Serial.print(" kI: "); Serial.print(kI);
  // Serial.print(" kD: "); Serial.print(kD);

  int16_t correction = kP * P + kI * I + kD * D;

  last_error = error;

  int16_t left_speed  = BASE_SPEED + correction;
  int16_t right_speed = BASE_SPEED - correction;

  left_speed  = constrain(left_speed,  0, 255);
  right_speed = constrain(right_speed, 0, 255);

  Right_Motor_Forward(MOTOR_PIN_A1, MOTOR_PIN_A2, right_speed);
  Left_Motor_Forward(MOTOR_PIN_B1, MOTOR_PIN_B2, left_speed);
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

  if (sensor_sum == 0)
  {
    if (last_error > 0) return 2;
    if (last_error < 0) return -2;
    return 0; 
  }

  

  return weighted_sum / sensor_sum;
}

/**
 * @brief Handle Bluetooth input for PID tuning
 * 
 * Expected input format: 'p' followed by kP value, 'i' followed by kI value, 'd' followed by kD value
 * Example: "p25.0" to set kP to 25.0
 */
void handleBT()
{
  if (!Serial.available()) return;

  char type = Serial.read();
  float value = Serial.parseFloat();

  if (type == 'p') kP = value;
  else if (type == 'i') kI = value;
  else if (type == 'd') kD = value;

  kP = constrain(kP, 0, 100);
  kI = constrain(kI, 0, 10);
  kD = constrain(kD, 0, 100);

  // Serial.print(type);
  // Serial.print(" = ");
  // Serial.println(value);
}

void Read_Sensors(uint8_t *sensor_array, uint8_t *sensor_reads)
{
  for (uint8_t i = 0; i < ARRAY_SIZE; i++)
  {
    sensor_reads[i] = digitalRead(sensor_array[i]);
    //delay(10); 
  }
}