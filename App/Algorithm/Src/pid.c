/*
 * pid.c
 *
 *  Created on: 2026. 6. 5.
 *      Author: user
 */


#include "pid.h"


static PID_Controller_t pid = {kp, ki, kd, d_t, 0, 0, i_lim};

/**
 * @brief PID 연산 수행 함수 (매 제어 주기마다 호출)
 */
int16_t PID_Compute(int16_t curr_error)
{
	// LPF 적용을 위한 알파값
	int16_t alpha = 8;

    // 1. 현재 오차 계산
    float error = (float)curr_error;

    // 2. P 항 (비례) 계산
    float p_term = pid.Kp * error;

    // 3. I 항 (적분) 계산 및 Anti-Windup 처리
    // 이산 시간 적분: 오차 * dt를 기존 누적값에 더함
    pid.i_sum += error * pid.dt;

    // 모터가 따라오지 못할 때 오차가 무한정 쌓이는 것을 방지
    if (pid.i_sum > pid.i_limit)  pid.i_sum = pid.i_limit;
    if (pid.i_sum < -pid.i_limit) pid.i_sum = -pid.i_limit;

    float i_term = pid.Ki * pid.i_sum;

    // 4. D 항 (미분) 계산
    // 이산 시간 미분: (현재 오차 - 직전 오차) / dt

    //float d_term = pid.Kd * ((error - pid.prev_error) / pid.dt);


    // 5. 최종 출력 합산
    float output = p_term + i_term;

    // 7. 다음 주기를 위해 현재 오차를 과거 데이터로 저장
    pid.prev_error = error;

    int16_t filtered_output = ((pid.prev_output * alpha) + (output * (10 - alpha))) / 10;
	pid.prev_output = (int16_t)output;
    return filtered_output;
}

/**
 * @brief PID 상태 초기화 (상태가 급격히 바뀔 때 오차 누적 초기화용)
 */
void PID_Reset(void)
{
    pid.prev_error = 0.0f;
    pid.i_sum = 0.0f;
}
