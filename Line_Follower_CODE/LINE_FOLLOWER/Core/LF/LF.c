/*
 * LF.c
 *
 *  Created on: 2026. gada 24. maijs
 *      Author: Rudolfs
 */
#include "main.h"
#include "LF.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;


void cmd_service(char *cmd, float *P, float *I, float *D, uint16_t *base_speed)
{
	static float pvalue, ivalue, dvalue;
	uint16_t speed;


	/* THIS IS TO BE USED WITH PID APP */
	//		  if(sscanf((char*)rx_buffer, "P=%d I=%d D=%d", &pvalue, &ivalue, &dvalue) == 1)
	//		  {
	//			  P = pvalue;
	//			  I = ivalue;
	//			  D = dvalue;
	//		  }

	if(sscanf(cmd, "P=%f", &pvalue) == 1)
		*P = pvalue;

	else if(sscanf(cmd, "I=%f", &ivalue) == 1)
		*I = ivalue;

	else if(sscanf(cmd, "D=%f", &dvalue) == 1)
		*D = dvalue;

	else if(strcmp(cmd, "stop") == 0)
	{
		stop();
	}

	else if(strcmp(cmd, "spin") == 0)
	{
		spin();
	}

	else if(sscanf(cmd, "set speed %hu", &speed) == 1)
	{
		if(speed > MAX_SPEED) speed = MAX_SPEED;
		if(speed < MIN_SPEED) speed = MIN_SPEED;

		*base_speed = speed;
	}
}



void forward(uint16_t speed)
{
	HAL_GPIO_WritePin(nSleep_GPIO_Port, nSleep_Pin, GPIO_PIN_SET);
	// Motor A
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed);

	// Motor B
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, speed);
}

void reverse(uint16_t speed)
{
	// Motor A
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);

	// Motor B
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
}

void set_right_motor(int16_t speed)
{
    if(speed >= 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, speed);
    }
    else
    {
        speed = -speed;

        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
    }
}

void set_left_motor(int16_t speed)
{
    if(speed >= 0)
    {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed);
    }
    else
    {
    	speed = -speed;
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
    }
}

void stop()
{
	HAL_GPIO_WritePin(nSleep_GPIO_Port, nSleep_Pin, GPIO_PIN_RESET);
	// Motor A
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MAX_SPEED);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, MAX_SPEED);

	// Motor B
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MAX_SPEED);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, MAX_SPEED);
}


void spin()
{
	// Motor A
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 50000);

	// Motor B
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 50000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

	HAL_Delay(500);

	stop();
}

float read_sensors(uint16_t *s_arr, uint8_t *sVal_arr, int8_t *weights, float *prevErr)
{

	int32_t weighted_sum = 0;
	int32_t active_sensors = 0;

	for(uint8_t i = 0; i < ARRAY_SIZE; i++)
	{
		sVal_arr[i] = HAL_GPIO_ReadPin(GPIOB, s_arr[i]);

		if(sVal_arr[i])
		{
			weighted_sum += weights[i];
			active_sensors++;
		}
	}

	if(active_sensors > 0)
	    return (float)weighted_sum / active_sensors;

	else return *prevErr;
}

















