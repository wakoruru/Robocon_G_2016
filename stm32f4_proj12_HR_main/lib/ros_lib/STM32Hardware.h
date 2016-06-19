#pragma once

#include "config/stm32plus.h"
#include "hardware/UsartInterruptWithBuffer.h"
#include "hardware/UsbDeviceCdcComPort.h"

class STM32Hardware {

public:
	STM32Hardware(ROSSERIAL_PORT* _com , long baud= 57600){
		com = _com;
		baud_ = baud;
	}
	STM32Hardware()
	{
		com = new ROSSERIAL_PORT(57600);
		baud_ = 57600;
	}
	STM32Hardware(STM32Hardware& h){
		this->baud_ = h.baud_;
	}

	void setBaud(long baud){
		this->baud_= baud;
	}

	int getBaud(){return baud_;}

	void init(){
		//iostream->begin(baud_);
	}

	int read(){
		if(com->dataAvailable()){
			return com->receive();
		}
		else{
			return -1;
		}
	};

	void write(uint8_t* data, int length){
		for(int i=0; i<length; i++){
			while( !com->readyToSend() );
			com->send(data[i]);
		}

	}

	unsigned long time(){return MillisecondTimer::millis();}

protected:
	ROSSERIAL_PORT* com;
	long baud_;
};
