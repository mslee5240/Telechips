void fire_siren(int repeat) {
	int frequency = 700;	// 700 ~ 1500

	set_buzzer(frequency);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	for (int i = 0; i < repeat; i++) {
		for (int j = 0; j < 22; j++) {
			frequency += 35;
			set_buzzer(frequency);
			HAL_Delay(20);
		}
		for (int j = 0; j < 53; j++) {
			frequency -= 15;
			set_buzzer(frequency);
			HAL_Delay(20);
		}
		noTone();
	}
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void ambulance_siren(int repeat) {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    for (int i = 0; i < repeat; i++) {
        for (int j = 0; j < 10; j++) {
            set_buzzer(1200); // 높은 톤
            HAL_Delay(100);   // 짧게 유지
            set_buzzer(900);  // 낮은 톤
            HAL_Delay(100);   // 짧게 유지
        }
        noTone(); // 끄기
        HAL_Delay(200);
    }

    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void close_buzzer() {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	setBuzzer(1000); // 1kHz로 세팅
	HAL_Delay(70);
	setBuzzer(2000); // 2kHz로 세팅
	HAL_Delay(70);
	setBuzzer(3000); // 3kHz로 세팅
	HAL_Delay(70);
	setBuzzer(4000); // 4kHz로 세팅
	HAL_Delay(70);

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void open_buzzer() {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	setBuzzer(261); // 1kHz로 세팅
	HAL_Delay(70);
	setBuzzer(329); // 2kHz로 세팅
	HAL_Delay(70);
	setBuzzer(392); // 3kHz로 세팅
	HAL_Delay(70);
	setBuzzer(554); // 4kHz로 세팅
	HAL_Delay(70);

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}