#include "Sin_wave_pwm.h"
#include "tim.h"


volatile uint32_t index;

uint16_t sineTable1[PWM_RESOLUTION];
uint16_t sineTable2[PWM_RESOLUTION];

void DWT_Delay(uint32_t us) {
    uint32_t us_count = (SystemCoreClock / 1000000) * us;
    uint32_t start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < us_count);
}

void generation_sine(void)
{
	for (int i = 0; i<PWM_RESOLUTION; i++)
	{
		sineTable1[i] = (uint16_t)((sin(2 * PI * i / PWM_RESOLUTION) + 1) * (htim3.Init.Period / 2));
		sineTable2[i] = (uint16_t)((sin(2 * PI * (i + PWM_RESOLUTION / 2) / PWM_RESOLUTION) + 1) * (htim3.Init.Period / 2));
	}
}

void Sin_wave_pwm_Init()

{
	htim3.Init.Period = (HAL_RCC_GetPCLK1Freq() / (htim3.Init.Prescaler + 1)) / PWM_FREQUENCY - 1;
	HAL_TIM_Base_Init(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	generation_sine();

	index = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
}

void Sin_wave_pwm_Handle()
{
	   volatile uint32_t dutyCycle1 = sineTable1[index];
	   volatile uint32_t dutyCycle2 = sineTable2[index];

	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, dutyCycle1);
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, dutyCycle2);

	   index = (index + 1) % PWM_RESOLUTION;
	  DWT_Delay(1000000 / (SINE_WAVE_FREQUENCY * PWM_RESOLUTION));
}

