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
	static uint8_t sensor_to_read = LEFT_SENSOR;
	static uint16_t dist[2] = {0, };

    for(;;)
    {
    	if(sensor_to_read == LEFT_SENSOR)
		{
    		dist[sensor_to_read] = Get_Distance(sensor_to_read);

    		Sensor_Trigger(RIGHT_SENSOR);

			sensor_to_read = RIGHT_SENSOR;
		}else
		{
			dist[sensor_to_read] = Get_Distance(sensor_to_read);

			Sensor_Trigger(LEFT_SENSOR);

			sensor_to_read = LEFT_SENSOR;
		}
    	xQueueSend(xQueueSensor, &dist, 0);
        // 신호만 보내고 바로 잠듦
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}


