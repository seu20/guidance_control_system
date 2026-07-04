/*
 * filter.c
 *
 *  Created on: 2026. 6. 6.
 *      Author: user
 */


#include "filter.h"

uint16_t Buffer_Filter(Ring_Buffer_t *buffer, uint16_t distance)
{
	// 합에서 오래된 값 차감
	buffer->sum -= buffer->dist[buffer->index];
	// 최신값 push
	buffer->dist[buffer->index] = distance;
	// 합 최신화
	buffer->sum += buffer->dist[buffer->index];
	// 가리키는 값의 인덱스 최신화
	buffer->index = (buffer->index + 1) % BUFFER_SIZE;
	// 평균값 리턴
	return (buffer->sum) / BUFFER_SIZE;
}
