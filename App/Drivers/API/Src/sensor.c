/*
 * driver_sensor.c
 *
 *  Created on: May 20, 2026
 *      Author: John
 */

#include <sensor.h>

// variables
static SensorData_t Sensors[2];
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// static functions
static uint16_t calculate_distance(uint16_t start_time, uint16_t end_time);


/*
 * ----------------------------------------------------------------
 * 					신호 트리거 함수
 * 	기능: 인자로 들어오는 인덱스에 따라 지정된 센서에 trigger 신호 전달
 */
void Sensor_Trigger(uint8_t sensor)
{
	// 트리거한 후에만 값을 받기
	Sensors[sensor].is_waiting = 1;

	if (sensor == LEFT_SENSOR)
	{
		HAL_GPIO_WritePin(GPIOB, S1_Trigger_Pin, GPIO_PIN_SET);
		// 다시 꺼줘야함
	}else
	{
		HAL_GPIO_WritePin(GPIOB, S2_Trigger_Pin, GPIO_PIN_SET);
		// 다시 꺼줘야함
	}
}

/*
 * ----------------------------------------------------------------
 * 					인터럽트에서 실행되는 함수
 * 	기능: 기다리는 센서의 값이 들어왔는지 확인하고 그 값을 구조체에 저장
 */

void Sensor_ISR(uint16_t GPIO_Pin)
{
	uint16_t current_time = __HAL_TIM_GET_COUNTER(&htim2);

	int idx;
	// 핀의 값에 따라 idx 설정
	if (GPIO_Pin == S1_Echo_Pin)		idx = 0;
	else if(GPIO_Pin == S2_Echo_Pin)	idx = 1;

	if (Sensors[idx].is_waiting)
	{
		// Rising Edge 일때 시작시간 저장
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_Pin) == GPIO_PIN_SET)
		{
			Sensors[idx].start_time = current_time;

		}else	// Falling Edge 일때 종료시간 저장
		{
			Sensors[idx].end_time = current_time;
			Sensors[idx].is_waiting = 0;
		}
	}
}

/*
 * ----------------------------------------------------------------
 * 					거리 읽는 함수
 * 	기능: 인자로 들어오는 인덱스에 따라 지정된 센서에 trigger 신호 전달
 */
uint16_t Get_Distance(uint8_t step)
{
	return calculate_distance(Sensors[step].start_time, Sensors[step].end_time);
}

/*
 * ----------------------------------------------------------------
 * 					거리 계산 함수
 * 	기능:
 */
static uint16_t calculate_distance(uint16_t start_time, uint16_t end_time)
{
	return (end_time - start_time) / US_Speed;
}


/* ----------------------------------------------------------------
* 					인터럽트 콜백 함수
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Sensor_ISR(GPIO_Pin);
}






