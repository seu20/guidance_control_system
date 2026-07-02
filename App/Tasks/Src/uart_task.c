/*
 * uart_task.c
 *
 *  Created on: 2026. 6. 7.
 *      Author: user
 */

#define CHECK_STACK

#include "uart_task.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

void vTaskUART(void* parameters)
{
	UARTLog_t uart_log;
	char tx_buffer[256];
#ifdef CHECK_STACK
	static UBaseType_t sensorStack = FIND_MIN, controlStack = FIND_MIN, uartStack = FIND_MIN;
#endif
	for(;;)
	{
		if (xQueueReceive(xQueueUART, &uart_log, portMAX_DELAY) == pdTRUE)
		{
			char* sensor_state;
			if (uart_log.state == SEARCH_STATE)
			{
				sensor_state = "SEARCH MODE";
			}else if (uart_log.state == LOCKON_STATE)
			{
				sensor_state = "LOCKON MODE";
			}
#ifdef CHECK_STACK
			UBaseType_t newStackVal;
			newStackVal = uxTaskGetStackHighWaterMark(xSensorScannerHandle);
			if (newStackVal > sensorStack)	sensorStack = newStackVal;
			newStackVal = uxTaskGetStackHighWaterMark(xControlHandle);
			if (newStackVal > controlStack)	controlStack = newStackVal;
			newStackVal = uxTaskGetStackHighWaterMark(xUARTHandle);
			if (newStackVal > uartStack)	uartStack = newStackVal;
#endif
			sprintf(tx_buffer,
					"\033[2J\033[H"
					"Left distance: %d\r\n"
					"Right distance: %d\r\n"
					"Steer: %d\r\n"
					"State: %s\r\n"
#ifdef CHECK_STACK
					"-----------------------\r\n"
					"Left Stack Memory\r\n"
					"sensorStack = %lu\r\n"
					"controlStack = %lu\r\n"
					"uartStack = %lu\r\n"
#endif
					"-----------------------\r\n",
					uart_log.l_dist,
					uart_log.r_dist,
					uart_log.steer,
					sensor_state,
#ifdef CHECK_STACK
					sensorStack,
					controlStack,
					uartStack
#endif
					);

			HAL_UART_Transmit(&huart2, (uint8_t *)tx_buffer, strlen(tx_buffer), 50);
		}
	}
}

