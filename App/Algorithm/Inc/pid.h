/*
 * driver_pid.h
 *
 *  Created on: 2026. 6. 5.
 *      Author: user
 */

#ifndef CUSTOM_INC_DRIVER_PID_H_
#define CUSTOM_INC_DRIVER_PID_H_

#include <stdint.h>

//defines
#define kp		1.5f
#define	ki		0.2f
#define kd		0.05f
#define d_t		0.02f
#define	i_lim	50.0f

// struct
typedef struct {
    // 제어 게인
    float Kp;
    float Ki;
    float Kd;

    // 제어 주기 (초 단위, 예: 20ms면 0.02f)
    float dt;

    // 과거 데이터 (상태 변수)
    float prev_error;
    float i_sum;

    // 제어 한계값 (Saturation & Anti-Windup)
    float i_limit;   // I항의 누적 한계치
} PID_Controller_t;


//functions
int16_t PID_Compute(int16_t);
void PID_Reset(void);

#endif /* CUSTOM_INC_DRIVER_PID_H_ */
