#ifndef SINEWAVE_SINEWAVE_PWM_
#define SINEWAVE_SINEWAVE_PWM_

#include <math.h>

#define PI 3.14159265
#define SINE_WAVE_FREQUENCY 20 // Frequency of the sine wave (20 Hz)
#define PWM_RESOLUTION 10000   // Resolution of the sine wave (number of steps)
#define PWM_FREQUENCY 20000   // Frequency of the PWM signal (20 kHz)

void Sin_wave_pwm_Init(void);
void Sin_wave_pwm_Handle(void);
#endif /* SINEWAVE_SINEWAVE_PWM_ */
