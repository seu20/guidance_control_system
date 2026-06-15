/*
 * sensor_task.c
 *
 *  Created on: May 20, 2026
 *      Author: John
 */

#include "sensor_task.h"

void vTaskSensorScanner(void* parameters)
{
	// 지역 변수로 어떤 센서를 읽을지
	static uint8_t step = LEFT_SENSOR;
	static uint16_t dist[2] = {0, };

    TickType_t xLastWakeUpTime = xTaskGetTickCount();
    const TickType_t xBlockTime = pdMS_TO_TICKS(10);

    for(;;)
    {
    	if(step == LEFT_SENSOR)
		{
    		dist[step] = Get_Distance(step);

    		xQueueSend(xQueueSensor, &dist, 0);

    		Sensor_Trigger(RIGHT_SENSOR);

			step = RIGHT_SENSOR;
		}else
		{
			dist[step] = Get_Distance(step);

			Sensor_Trigger(LEFT_SENSOR);

			step = LEFT_SENSOR;
		}
        // 신호만 보내고 바로 잠듦
        vTaskDelayUntil(&xLastWakeUpTime, xBlockTime);
    }
}


