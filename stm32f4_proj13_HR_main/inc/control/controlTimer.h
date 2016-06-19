#pragma once

#include "config/timer.h"

template<class TTimer, class TClass>
class ControlTimer : public TTimer {
	public:
		ControlTimer(TClass* _target, uint16_t freq, uint8_t _priority=0):target(_target),priority(_priority){
			this->setTimeBaseByFrequency(60000, 60000/freq - 1); // 1000Hz: 1ms
		}
		~ControlTimer(){}
		void bind(void (TClass::*callback)(TimerEventType,uint8_t)){
			this->disablePeripheral();
			this->TimerInterruptEventSender.insertSubscriber(
					TimerInterruptEventSourceSlot::bind(target, callback)
					);
			this->setNvicPriorities(priority);
			this->enableInterrupts(TIM_IT_Update);
			this->enablePeripheral();
		}
	private:
		TClass *target;
		uint8_t priority;
};
