/*
 * driver_motor.h
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */

#ifndef DRIVERS_API_INC_MOTOR_H_
#define DRIVERS_API_INC_MOTOR_H_

#include "main.h"

//defines
#define PWM_Step	5
#define PWM_Shift	50
#define	PWM_MAX		2500
#define PWM_MIN		500
#define DIST_MAX	400
#define DIST_MIN	3
#define DIST_REF	30
#define PWM_START	1500


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
void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel);
uint8_t is_Motor_Limit(SensorCaught_t direction);
#endif /* DRIVERS_API_INC_MOTOR_H_ */
