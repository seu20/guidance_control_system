/*
 * driver_motor.c
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */

#include <motor.h>

//defines
#define PWM_Step	5
#define PWM_Shift	83
#define	PWM_MAX		2000
#define PWM_MIN		1000
#define DIST_MAX	400
#define DIST_MIN	3
#define DIST_REF	30

extern TIM_HandleTypeDef htim3;
MotorPWM_t motor = { &htim3, TIM_CHANNEL_1, PWM_START, DIR_RIGHT };

/*
 * ----------------------------------------------------------------
 * 					센서 회전 함수
 * 	기능: 인자로 들어오는 인덱스에 따라 지정된 센서에 trigger 신호 전달
 */
void Motor_Rotate(void)
{
	uint16_t curr_CCR = motor.CCR;
	uint16_t next_CCR = curr_CCR + (PWM_Step * motor.direction);

	if (next_CCR >= PWM_MAX)
	{
		next_CCR = PWM_MAX;
		motor.direction = DIR_LEFT;
	}else if (next_CCR <= PWM_MIN)
	{
		next_CCR = PWM_MIN;
		motor.direction = DIR_RIGHT;
	}

	__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);
	motor.CCR = next_CCR;
}

/*
 * ----------------------------------------------------------------
 * 					센서 한쪽에만 잡혔을때 그 방향으로 날개 꺾어줌
 * 	기능:
 */
void Motor_Shift(SensorCaught_t sensor_caught)
{
	uint16_t curr_CCR = motor.CCR;
	uint16_t next_CCR;
	if (sensor_caught == LEFT)
	{
		next_CCR = curr_CCR - PWM_Shift;
		if (next_CCR <= PWM_MIN)	next_CCR = PWM_MIN;
		motor.CCR = next_CCR;
		__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);
	}else if (sensor_caught == RIGHT)
	{
		next_CCR = curr_CCR + PWM_Shift;
		if (next_CCR >= PWM_MAX)	next_CCR = PWM_MAX;
		motor.CCR = next_CCR;
		__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);
	}
}

/*
 * ----------------------------------------------------------------
 * 					어느 센서에 표적이 잡혔나
 * 					(양쪽, 왼쪽, 오른쪽, 양쪽 다 안잡힘)
 * 	기능:
 */
SensorCaught_t Which_Sensor(uint16_t l_distance, uint16_t r_distance)
{
	// 큐에서 넘어온 거리 값을 기준으로 범위 판정 (기존 DIST_REF 사용)
	uint8_t left_in  = (l_distance > DIST_MIN && l_distance <= DIST_REF);
	uint8_t right_in = (r_distance > DIST_MIN && r_distance <= DIST_REF);

	if (left_in && right_in)        return BOTH;
	else if (left_in && !right_in)  return LEFT;
	else if (!left_in && right_in)  return RIGHT;

	return NONE;
}

/*
 * ----------------------------------------------------------------
 * 					어느 센서에 표적이 잡혔나
 * 					(양쪽, 왼쪽, 오른쪽, 양쪽 다 안잡힘)
 * 	기능:
 */
void Motor_PID_Control(int16_t steer_val)
{
	int16_t curr_CCR = (int16_t)motor.CCR;
	uint16_t next_CCR = curr_CCR + steer_val;

	if (next_CCR >= PWM_MAX)	next_CCR = PWM_MAX;
	if (next_CCR <= PWM_MIN)	next_CCR = PWM_MIN;

	motor.CCR = next_CCR;
	__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);


}
