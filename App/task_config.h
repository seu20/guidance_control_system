/*
 * task_config.h
 *
 *  Created on: 2026. 6. 5.
 *      Author: user
 */

#ifndef TASK_CONFIG_H_
#define TASK_CONFIG_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


typedef enum {
	SEARCH_STATE,
	LOCKON_STATE
}SensorState_t;

typedef struct {
	int16_t l_dist;
	int16_t r_dist;
	int16_t steer;
	SensorState_t state;
}UARTLog_t;


extern QueueHandle_t xQueueSensor;
extern QueueHandle_t xQueueUART;
extern TaskHandle_t xSensorScannerHandle;
extern TaskHandle_t xControlHandle;
extern TaskHandle_t xUARTHandle;
#endif /* TASK_CONFIG_H_ */
