#include <math.h>
#include "config/stm32plus.h"
#include "config/timer.h"
#include "config/timing.h"
#include "devices/motor.h"
using namespace stm32plus;

using MOTOR_TIMER = Timer4<
		Timer4InternalClockFeature,
		TimerChannel1Feature<>,
		TimerChannel2Feature<>,
		Timer4GpioFeature<
			TIMER_REMAP_FULL,
			TIM4_CH1_OUT,
			TIM4_CH2_OUT
		>
>;
using MOTOR_CHA = TimerChannel1Feature<>;
using MOTOR_CHB = TimerChannel2Feature<>;

int main(void){
	MillisecondTimer::initialise();
	Motor< MOTOR_TIMER, MOTOR_CHA, MOTOR_CHB > motor;
	while(1){
		for( int i=0; i<1000;i++){
			motor.setOutput(sinf(2*M_PI*i/1000));
			MillisecondTimer::delay(10);
		}
	}
}
