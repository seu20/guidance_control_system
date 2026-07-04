#  Guided Control System Simulator (STM32 & FreeRTOS)

> **STM32F103RB** 환경에서 **FreeRTOS**를 활용하여 구현한 초음파 센서를 활용한 PID 제어를 통해 목표를 추적하는 시스템입니다.

## 데모 영상
- **좌측: 유도센서**
- **우상단: 터미널 결과 출력 (양쪽 센서 측정값, PID 출력값, 상태, 각 태스크에 남아있는 스택 공간)**
  <video controls src="Images/taerget_tracker demo.mp4" title="Title"></video>
**SEARCH_MODE -> LOCKON_MODE -> SEARCH MODE 상태 변환**
---

## 기술 스택
- **HW:** STM32F103RB (ARM Cortex-M3), HC-SR04 2개(센서 모듈), 서브 모터 1개(SG-90)
- **SW:** STMCubeIDE, STMCubeMX, Putty, SeggerSystemView ( 디버깅용 )
- **OS:** FreeRTOS
- **사용 언어:** C

## 설계 구조
- **태스크 분류**
  - (1) Task_sensor (Priority 2) : 20ms 주기로 초음파 센서를 Trigger

  - (2) Task_Control (Priority 3, 주기: 20ms) : 주기로 수신된 거리와 각도 데이터를 PID 함수를 통해 날개를 제어한다. 양 센서의 거리 데이터를 통해 상태 변환

  - (3) Task_uart (Priority 1, 주기: 100ms) : 현재 상태 (SEARCH MODE, LOCKON MODE), 양 센서의 탐지 거리, PID 출력의 결과, 각 태스크의 스택 사용량 (선택)
<br>

- **FSM(상태머신)**
 ```mermaid
stateDiagram-v2
    direction LR

    [*] --> SEARCH
    
    SEARCH --> Shift : 양 센서 중 한쪽에만 표적이 탐지됐을 시 그 방향으로 15도 꺾음 (CAUGHT = RIGHT or LEFT)
    
    Shift --> LOCKON : 양 센서에 표적이 탐지됐을시 추적 시작 (CAUGHT = BOTH)

    LOCKON --> SEARCH : 타겟 놓침 (CAUGHT = NONE)
```

- **Real-time Task Scheduling:** FreeRTOS를 이용한 센서 읽기, 제어 연산, 모터 출력 태스크 분리
- **PID Control:** 타겟과의 거리 및 각도 유지를 위한 정밀 제어 알고리즘 적용. 




## 제어 로직
본 프로젝트에서는 타겟 추적을 위해 아래와 같은 **PID 제어식**을 사용했다.

$$u(t) = K_p e(t) + K_i \int_{0}^{t} e(\tau) d\tau + K_d \frac{de(t)}{dt}$$



#### 1. 가변 게인 PID 제어 
타겟과의 거리에 따라 제어 강도를 동적으로 조절하는 **Gain Scheduling** 기법을 적용했습니다.

* **배경:** 타겟이 멀리 있을 때는 완만하게 추적하고, 가까워질수록 제어 반응성을 높여 명중률을 향상시켜야 합니다.
* **구현:** 타겟과의 거리($d$)에 반비례하도록 $K_p$ 게인을 실시간으로 업데이트합니다.
    $$K_p(d) = K_{p,base} \times \frac{d_{ref}}{d_{current}}$$

---

#### 2. 신호 처리 및 필터링 (Signal Processing)
저가형 초음파 센서의 하드웨어적 한계를 소프트웨어적으로 극복했습니다.

##### 큐 기반 이동 평균 필터 (Moving Average Filter)
센서값이 실제 거리보다 튀는 현상을 완화하기 위해 링 버퍼 (Ring Buffer) 자료구조를 사용해 3개값의 평균을 활용하는 방식을 채택했음.
* **공식:** 
  $$y[n] = \frac{1}{N} \sum_{i=0}^{N-1} x[n-i]$$

* **설정:**  **$N = 3$** (윈도우 크기 설정)
    * 시스템 딜레이와 노이즈 억제간의 타협점을 설정함.

```C
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

```
##### 지수 이동 평균 필터(EMA)
가공하지 않은 PID 출력 값의 입력에 의해 서보모터의 Jitter 현상이 발생. 직전 PID 출력값과 현재 출력값을 EMA 필터를 통해 평활화하였음.
* **공식:** $y[n] = (1- \alpha) \cdot x[n] + \alpha \cdot y[n-1]$
* **설정:** $\alpha = 0.3$ (현재 데이터에 더욱 높은 값을 주어 움직이는 표적을 재빠르게 따라갈 수 있도록 설정)


```C
int16_t PID_Compute(int16_t curr_error)
{
    // LPF 적용을 위한 알파값
    int16_t alpha = 3;
    
    // ... 축약 및 기존 연산 로직 ...
    
    int16_t filtered_output = ((pid.prev_output * alpha) + (output * (10 - alpha))) / 10;
    pid.prev_output = (int16_t)output;
    return filtered_output;
}
```
---

## Scheduling 주기 & 메모리 최적화
구현 이외에 정확한 엄격한 스케쥴링 주기와 메모리 최적화를 적용했다.
##### Scheduling
SEGGER Systemview를 통해 정확히 20ms 주기에 task가 실행되는것을 확인했다.
![alt text](<Images/Scheduling Period.png>)

##### 메모리 최적화
uxTaskGetStackHighWaterMark() 함수를 통해 각 태스크들의 여분 스택 메모리를 확인후 32 ( **Depth of Stack Memory로 128byte** ) 공간이 남도록 설정함.


