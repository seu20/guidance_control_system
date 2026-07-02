/*
 * driver_motor.c
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */

#include "motor.h"

MotorPWM_t motor;

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
    motor.htim = htim;
    motor.channel = channel;
    motor.CCR = PWM_START;
    motor.direction = DIR_RIGHT;

    // PWM 하드웨어 시작도 아예 모터 드라이버가 알아서 하게 위임
    HAL_TIM_PWM_Start(motor.htim, motor.channel);
    __HAL_TIM_SET_COMPARE(motor.htim, motor.channel, motor.CCR);
}

/*
 * ----------------------------------------------------------------
 * 					센서 회전 함수
 * 	기능: 인자로 들어오는 인덱스에 따라 지정된 센서에 trigger 신호 전달
 */
void Motor_Rotate(void)
{
    int32_t next_CCR = (int32_t)motor.CCR + ((int32_t)PWM_Step * (int32_t)motor.direction);

    if (motor.direction == DIR_RIGHT)
    {
        if (next_CCR >= (int32_t)PWM_MAX)
        {
            next_CCR = (int32_t)PWM_MAX;
            motor.direction = DIR_LEFT;
        }
    }
    else if (motor.direction == DIR_LEFT)
    {
        if (next_CCR <= (int32_t)PWM_MIN)
        {
            next_CCR = (int32_t)PWM_MIN;
            motor.direction = DIR_RIGHT;
        }
    }

    motor.CCR = (uint16_t)next_CCR;
    __HAL_TIM_SET_COMPARE(motor.htim, motor.channel, motor.CCR);
}

uint8_t is_Motor_Limit(SensorCaught_t direction)
{
	// 현재 모터 각도가 한계인지 검사
	if (((motor.CCR <= (PWM_MIN + PWM_Shift)) && (direction == RIGHT)) || ((motor.CCR == (PWM_MAX - PWM_Shift)) && (direction == LEFT)))	return 1;
	return 0;
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
	if (sensor_caught == RIGHT)
	{

		next_CCR = curr_CCR - PWM_Shift;
		if (next_CCR <= PWM_MIN)	next_CCR = PWM_MIN;
		motor.CCR = next_CCR;
		__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);
	}else if (sensor_caught == LEFT)
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
	int32_t next_CCR = (int32_t)motor.CCR + steer_val;

	if (next_CCR >= PWM_MAX)	next_CCR = PWM_MAX;
	if (next_CCR <= PWM_MIN)	next_CCR = PWM_MIN;

	motor.CCR = next_CCR;
	__HAL_TIM_SET_COMPARE(motor.htim, motor.channel, next_CCR);


}
