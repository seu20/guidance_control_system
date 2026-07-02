/*
 * test_task.c
 *
 *  Created on: 2026. 6. 15.
 *      Author: user
 */

#include "task_config.h"

void vTaskTest(void* parameters)
{
	uint16_t dist[2] = {0, 0};
	TickType_t xLastWakeUpTime = xTaskGetTickCount();
	const TickType_t xBlockTime = pdMS_TO_TICKS(20);
	for(;;)
	{
		xQueueSend(xQueueSensor, &dist, 0);

		vTaskDelayUntil(&xLastWakeUpTime, xBlockTime);
	}
}
