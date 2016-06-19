#pragma once
/*
namespace stm32plus{
template<class TDMA,class TADC,class _Tacd>
	class PSD_2ch:public TDMA,public TADC{
	private:
		volatile bool _ready;
		volatile uint16_t readBuffer[2];
		TDMA dma;
		TADC adc;
	public:
		PSD_2ch(){
			dma.DmaInterruptEventSender.insertSubscriber(DmaInterruptEventSourceSlot::bind(this,&PSD_2ch::onComplete));
			dma.enableInterrupts(_Tadc::COMPLETE);
			dma.beginRead(readBuffer,2);
		}
		void PSD_read(uint16_t *read[2]){
			while(!_ready);
			_ready=false;
			read[0] = readBuffer[0];
			read[1] = readBuffer[1];
		}
		void onComplete(DmaEventType det) {
			if(det==DmaEventType::EVENT_COMPLETE)
			_ready=true;
		}
	};
}
*/
