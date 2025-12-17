#ifndef GPIO_H
#define GPIO_H

#define MOTOR_PIN_A1 5
#define MOTOR_PIN_A2 11
#define MOTOR_PIN_B1 9
#define MOTOR_PIN_B2 10


void GPIO_Init(void)
{
  pinMode(MOTOR_PIN_A1, OUTPUT);
  pinMode(MOTOR_PIN_A2, OUTPUT);
  pinMode(MOTOR_PIN_B1, OUTPUT);
  pinMode(MOTOR_PIN_B2, OUTPUT);

  Serial.println("GPIO Initialzied!");
}

#endif // GPIO_H