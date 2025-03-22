#include "main.h"

// stdout에 UART0_transmit을 연결하여 printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	// 모든 주변장치 초기화 및 전역 인터럽트 허용
	init_all();
	
	while (1)
	{
		for (int i = 0; i < NUM_SENSORS; i++) {
			current_sensor = i;     // 현재 측정할 센서 인덱스
			sensor_done[i] = 0;     // 플래그 초기화
			
			sensor_trigger(i);      // 해당 센서에 트리거 펄스 발생

			uint16_t distance;
			distance = calculate_distance(sensor_pulse_width[i]);
		
			printf("sensor[%d] distance: %d", i, distance);
			
			_delay_ms(10);
		}
	}
	
	return 0;
}

// 모든 주변장치 초기화
void init_all(void)
{
	init_timer0();

	init_uart0();
	init_uart1();
	
	init_ultrasonic();
	
	sei();	// 전역 인터럽트 허용
	
	
	stdout = &OUTPUT;   // 표준 출력(stdout)을 UART0의 OUTPUT 스트림에 연결
}