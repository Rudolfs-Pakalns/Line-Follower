/*
 * LF.h
 *
 *  Created on: 2026. gada 24. maijs
 *      Author: Rudolfs
 */
#include "main.h"

#ifndef LF_LF_H_
#define LF_LF_H_

#define MAX_SPEED 		65535
#define MIN_SPEED 		10000
#define ARRAY_SIZE		5

void cmd_service(char *cmd, float *P, float *I, float *D, uint16_t *base_speed);
void forward(uint16_t speed);
void reverse(uint16_t speed);
void set_right_motor(int16_t speed);
void set_left_motor(int16_t speed);
void stop();
void spin();
void set_base_speed(uint16_t *current_speed, uint16_t new_speed);
float read_sensors(uint16_t *s_arr, uint8_t *sVal_arr, int8_t *weights, float *prevErr);

#endif /* LF_LF_H_ */
