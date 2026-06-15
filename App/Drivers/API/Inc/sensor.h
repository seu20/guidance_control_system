/*
 * driver_sensor.h
 *
 *  Created on: May 20, 2026
 *      Author: John
 */

#ifndef CUSTOM_INC_DRIVER_SENSOR_H_
#define CUSTOM_INC_DRIVER_SENSOR_H_

// includes
#include "main.h"


// defines
#define US_Speed	58
#define LEFT_SENSOR		0
#define RIGHT_SENSOR	1

// struct
typedef struct {
	uint16_t start_time;
	uint16_t end_time;
	uint8_t is_waiting;
} SensorData_t;

// functions
void Sensor_Trigger(uint8_t sensor);
uint16_t Get_Distance(uint8_t step);
void Sensor_ISR(uint16_t);

#endif /* CUSTOM_INC_DRIVER_SENSOR_H_ */
