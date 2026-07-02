/*
 * control_task.c
 */

#include "control_task.h"

static SensorState_t state = SEARCH_STATE;
static Ring_Buffer_t L_Buffer = {{0, }, 0 , 0};
static Ring_Buffer_t R_Buffer = {{0, }, 0 , 0};
Ring_Buffer_t *p_lbuffer = &L_Buffer;
Ring_Buffer_t *p_rbuffer = &R_Buffer;



void vTaskControl(void* parameters)
{
	static uint8_t uart_count = 0;
	uint16_t rcv_dist[2];     // 큐에서 꺼낸 이번 주기 거리 값 [좌, 우]
	int16_t steer_val = 0;

	TickType_t xLastWakeUpTime = xTaskGetTickCount();
	const TickType_t xBlockTime = pdMS_TO_TICKS(20);
	for(;;)
	{
		// 큐에서 데이터가 들어오면 깨어남 (20ms) 주기
		if(xQueueReceive(xQueueSensor, rcv_dist, portMAX_DELAY) == pdTRUE)
		{
			uint16_t l_filtered = Buffer_Filter(p_lbuffer, rcv_dist[0]);
			uint16_t r_filtered = Buffer_Filter(p_rbuffer, rcv_dist[1]);
			SensorCaught_t caught = Which_Sensor(l_filtered, r_filtered);
			switch(state)
			{
				// 탐지 모드
				case SEARCH_STATE:
					if (caught == BOTH)
					{
						PID_Reset();
						// 센서 양쪽에 잡히면 LOCKON으로 상태 변화
						state = LOCKON_STATE;
					}else if (caught == RIGHT || caught == LEFT)
					{
						// 모터 각도가 최대이면 무시하고 회전실행
						if (is_Motor_Limit(caught))
						{
							Motor_Rotate();
							continue;
						}
						// 한쪽에만 잡히면 그 방향으로 틀기
						Motor_Shift(caught);

					}else
					{
						// 모터 회전
						Motor_Rotate();
					}
					break;
				// 추적 모드
				case LOCKON_STATE:
					if (caught == BOTH)
					{
						steer_val = PID_Compute((int16_t)r_filtered - (int16_t)l_filtered);
						Motor_PID_Control(steer_val);
					}else if (caught == RIGHT || caught == LEFT)
					{
						// 모터 각도가 최대이면 무시하고 회전실행
						if (is_Motor_Limit(caught))
						{
							Motor_Rotate();
							continue;
						}
						// 한쪽에만 잡히면 그 방향으로 틀기
						Motor_Shift(caught);
					}else{
						state = SEARCH_STATE;
					}
					break;
			}
			uart_count++;

			// 500ms 주기로 uart log 출력
			if (uart_count >= 25)
			{
				//UART 구조체 선언
				UARTLog_t uart_log = {l_filtered, r_filtered, steer_val, state};
				uart_count = 0;
				xQueueSend(xQueueUART, &uart_log, 0);
			}
			xTaskDelayUntil(&xLastWakeUpTime, xBlockTime);
		}
	}
}
