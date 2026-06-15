/*
 * filter.h
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */

#ifndef ALGORITHM_INC_FILTER_H_
#define ALGORITHM_INC_FILTER_H_

#include <stdint.h>

#define BUFFER_SIZE	5

typedef struct {
	uint16_t dist[5];
	uint8_t index;
	uint16_t sum;
}Ring_Buffer_t;

uint16_t Buffer_Filter(Ring_Buffer_t *buffer, uint16_t distance);

#endif /* ALGORITHM_INC_FILTER_H_ */
