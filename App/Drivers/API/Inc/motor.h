/*
 * driver_motor.h
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */

#ifndef DRIVERS_API_INC_MOTOR_H_
#define DRIVERS_API_INC_MOTOR_H_

#include "main.h"


// variables
typedef enum {
    DIR_LEFT = -1,
    DIR_RIGHT   = 1
} MotorDir_t;

typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	uint16_t CCR;
	MotorDir_t direction;
} MotorPWM_t;

typedef enum {
	NONE,
	BOTH,
	LEFT,
	RIGHT
}SensorCaught_t;

// functions
void Motor_Rotate(void);
void Motor_Shift(SensorCaught_t);
void Motor_PID_Control(int16_t);
SensorCaught_t Which_Sensor(uint16_t l_distance, uint16_t r_distance);

#endif /* DRIVERS_API_INC_MOTOR_H_ */
