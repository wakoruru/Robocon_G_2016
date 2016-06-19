#pragma once

#include "config/stm32plus.h"
#include "config/timer.h"

namespace stm32plus{
	template<class TimMotor, class ChannelA, class ChannelB>
	class Motor : TimMotor{
		public:
			enum{
				MAX_COMPARE=840
			};
			Motor():TimMotor(){
				this->setTimeBaseByFrequency(42000000, MAX_COMPARE-1);
				ChannelA::initCompareForPwmOutput();
				ChannelB::initCompareForPwmOutput();
				this->enablePeripheral();
			}
			void setOutput(float duty){
				if(duty > 1.0f){
					duty = 1.0f;
				}
				else if(duty < -1.0f){
					duty = -1.0f;
				}
				duty = duty * 0.95;

				int16_t value = (int16_t)(duty * MAX_COMPARE/2);
				ChannelA::setCompare(MAX_COMPARE/2+value);
				ChannelB::setCompare(MAX_COMPARE/2-value);
			}
			inline void stop(){
				setOutput(0);
			}
	};
}
