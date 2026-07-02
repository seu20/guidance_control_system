/*
 * laser.h
 *
 *  Created on: 2026. 6. 27.
 *      Author: user
 */

#ifndef DRIVERS_API_INC_LASER_H_
#define DRIVERS_API_INC_LASER_H_

#include "main.h"

#define GPIOC_ODR_ADDRESS    	(GPIOC_BASE + 0x0CUL)
#define Byte_Offset 			(GPIOC_ODR_ADDRESS - PERIPH_BASE)


// 비트밴딩 연산
#define LASER_BB_ADDR			((volatile uint32_t*)(0x42000000UL  + (Byte_Offset * 32) + (4 * 4)))

// 레이저 전원 매크로
#define Laser_On				(*(LASER_BB_ADDR) = 1)
#define Laser_Off				(*(LASER_BB_ADDR) = 0)
#endif /* DRIVERS_API_INC_LASER_H_ */
