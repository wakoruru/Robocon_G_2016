/*
 * 20xx　/　xx　/　xx　/　若生 建
 * 
 * Purpose : 2016 Hybrid Robot
 * USB usart : Usart2[PA2,PA3]
 * Motor PWM : Timer1[PA8,PA10],Timer1[E9,E11,E13,E14],Timer8[PC6,PC7,PC8,PC9]
 * QEI Timer : Timer2[PA15,PB3],Timer3[PB4,PB5],Timer3[PC6,PC7],Timer4[PB6,PB7]
 * Servo pin : Usart3[PD8,PD9]
 */
/* Include -------------------------------------------------------------------*/
#include "mecha_lib/UHMwithF4dis_NMD.h"
/* usb */
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"
#include "usbh_hid_ps3.h"
/* Ros -----------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/
#define SELECT		btn[0]
#define L3			btn[1]
#define R3			btn[2]
#define START		btn[3]
#define UP			btn[4]
#define RIGHT		btn[5]
#define DOWN		btn[6]
#define LEFT		btn[7]
#define L2			btn[8]
#define R2			btn[9]
#define L1			btn[10]
#define R1			btn[11]
#define SANKAKU		btn[12]
#define MARU		btn[13]
#define BATSU		btn[14]
#define SHIKAKU		btn[15]
#define ANALOG		btn[16]
#define S_SELECT	btn_state[0]
#define S_L3		btn_state[1]
#define S_R3		btn_state[2]
#define S_START		btn_state[3]
#define S_UP		btn_state[4]
#define S_RIGHT		btn_state[5]
#define S_DOWN		btn_state[6]
#define S_LEFT		btn_state[7]
#define S1_L2		btn_state[8]
#define S1_R2		btn_state[9]
#define S1_L1		btn_state[10]
#define S1_R1		btn_state[11]
#define S_SANKAKU	btn_state[12]
#define S_MARU		btn_state[13]
#define S_BATSU		btn_state[14]
#define S_SHIKAKU	btn_state[15]
#define S_ANALOG	btn_state[16]
#define HR_Lcir()	uhm.motor1.Forward();  uhm.motor2.Forward();  uhm.motor3.Forward();  uhm.motor4.Forward()
#define HR_Rcir()	uhm.motor1.Backward(); uhm.motor2.Backward(); uhm.motor3.Backward(); uhm.motor4.Backward()
#define HR_For()	uhm.motor1.Backward(); uhm.motor2.Forward();  uhm.motor3.Backward(); uhm.motor4.Forward()
#define HR_Back()	uhm.motor1.Forward();  uhm.motor2.Backward(); uhm.motor3.Forward();  uhm.motor4.Backward()
#define HR_Left()	uhm.motor1.Forward(); uhm.motor2.Forward();  uhm.motor3.Backward(); uhm.motor4.Backward()
#define HR_Right()	uhm.motor1.Backward();  uhm.motor2.Backward(); uhm.motor3.Forward();  uhm.motor4.Forward()
/*
#define HR_For()	uhm.motor1.Forward()
#define HR_Back()	uhm.motor2.Forward()
#define HR_Right()	uhm.motor3.Forward()
#define HR_Left()	uhm.motor4.Forward()
*/
#define HR_Setpwm(a,b,c,d)	uhm.motor1.Setpwm(a);   uhm.motor2.Setpwm(b);   uhm.motor3.Setpwm(c);   uhm.motor4.Setpwm(d)
#define HR_Stop()	uhm.motor1.Stop();     uhm.motor2.Stop();     uhm.motor3.Stop();     uhm.motor4.Stop()
/* CallbackFunction ----------------------------------------------------------*/
bool SAFE=false;
ps3 con,before;
omn wheel,bwhe,fall;
USB_OTG_CORE_HANDLE           USB_OTG_Core_dev;
USBH_HOST                     USB_Host;
uint16_t btn[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool btn_state[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t fri[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
class USBTimer {
public:
  USBTimer(){
    timer.setTimeBaseByFrequency(1000, 5-1);
    timer.TimerInterruptEventSender.insertSubscriber(
	TimerInterruptEventSourceSlot::bind(this, &USBTimer::onInterrupt)
    );
    timer.setNvicPriorities(0);
    timer.enableInterrupts(TIM_IT_Update);
    timer.enablePeripheral();
  }
  void onInterrupt(TimerEventType tet,uint8_t timerNumber){
    if(tet==TimerEventType::EVENT_UPDATE){
    	/* Host Task handler */
    	USBH_Process(&USB_OTG_Core_dev , &USB_Host);
    }
  }
private:
  Timer5<Timer5InternalClockFeature,Timer5InterruptFeature> timer;
};

/* Main ----------------------------------------------------------------------*/
int main(void){
/*Valuable*/
	int i;
	uint8_t mode1=0,mode2=0,mode3=0,mode4=0;
	uint32_t Enc1=0,Enc2=0,Enc3=0,Enc4=0;
	float pwmval[4]={0,0,0,0};
	bool relay[4]={false,false,false,false};
	bool S_R1=false,S_R2=false,S_L1=false,S_L2=false;
/* Init Host Library */
	USBH_Init(&USB_OTG_Core_dev, USB_OTG_FS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks );
/*Nvic*/
	Nvic::initialise();
/*delay*/
	MillisecondTimer Milli;
	Milli.initialise();
/*UHM*/
	UHM uhm;
	uhm.led1.Off();
	uhm.led2.Off();
	uhm.led3.Off();
	uhm.led4.Off();
	uhm.buzz.pat_01();

	USBTimer timer;
/*Loop*/
	while(1){
		if(ps3_connected == 1){
			btn[0]  = HID_PS3_Data.button[0] == fri[0];
			btn[1]  = HID_PS3_Data.button[0] == fri[1];
			btn[2]  = HID_PS3_Data.button[0] == fri[2];
			btn[3]  = HID_PS3_Data.button[0] == fri[3];
			btn[4]  = HID_PS3_Data.button[0] == fri[4];
			btn[5]  = HID_PS3_Data.button[0] == fri[5];
			btn[6]  = HID_PS3_Data.button[0] == fri[6];
			btn[7]  = HID_PS3_Data.button[0] == fri[7];
			btn[8]  = HID_PS3_Data.button[1] == fri[0];
			btn[9]  = HID_PS3_Data.button[1] == fri[1];
			btn[10] = HID_PS3_Data.button[1] == fri[2];
			btn[11] = HID_PS3_Data.button[1] == fri[3];
			btn[12] = HID_PS3_Data.button[1] == fri[4];
			btn[13] = HID_PS3_Data.button[1] == fri[5];
			btn[14] = HID_PS3_Data.button[1] == fri[6];
			btn[15] = HID_PS3_Data.button[1] == fri[7];
			btn[16] = HID_PS3_Data.button[2];
			if( UP==false && (bwhe.flag[0]==true) ){
				fall.flag[0]=true;
			}else{
				fall.flag[0]=false;
			}
			bwhe.flag[0] = wheel.flag[0];

			if( DOWN==false && (bwhe.flag[1]==true) ){
				fall.flag[1]=true;
			}else{
				fall.flag[1]=false;
			}
			bwhe.flag[1] = wheel.flag[1];

			if( LEFT==false && (bwhe.flag[2]==true) ){
				fall.flag[2]=true;
			}else{
				fall.flag[2]=false;
			}
			bwhe.flag[2] = wheel.flag[2];

			if( RIGHT==false && (bwhe.flag[3]==true) ){
				fall.flag[3]=true;
			}else{
				fall.flag[3]=false;
			}
			bwhe.flag[3] = wheel.flag[3];
			/* Enc read */
		/*Motor*/
			pwmval[0]=wheel.rate/0.707;
			pwmval[1]=wheel.rate/0.707;
			pwmval[2]=wheel.rate/0.707;
			pwmval[3]=wheel.rate/0.707;
		//オムニっぽくしてみる(4/17)
			if(mode1 == 1 && mode2 == 1 && mode3 == 1 && mode4 == 1){
				if(DOWN==1){
					uhm.motor2.Backward();
					uhm.motor4.Backward();
				}else
				if(UP==1){
					uhm.motor2.Forward();
					uhm.motor4.Forward();
				}

				if(BATSU==1){
					uhm.motor1.Forward();
					uhm.motor3.Forward();
				}else
				if(SANKAKU==1){
					uhm.motor1.Backward();
					uhm.motor3.Backward();
				}

				if(LEFT==1 || SHIKAKU==1){
					HR_Left();
				}else
				if(MARU==1 || RIGHT==1){
					HR_Right();
				}

				if(UP==0 && SANKAKU==0 && DOWN==0 && BATSU==0 && MARU==0 && RIGHT==0 && LEFT==0 && SHIKAKU==0){
					HR_Stop();
				}else{
					HR_Setpwm(0.95,0.95,0.95,0.95);
				}
			}
			else if((UP) && !relay[1] && !relay[2] && !relay[3]){
				HR_For();
				uhm.led1.On();
				uhm.led2.Off();
				uhm.led3.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[0] =true;
			}else
			if((DOWN) && !relay[0] && !relay[2] && !relay[3]){
				HR_Back();
				uhm.led4.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led3.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[1] =true;
			}else
			if((LEFT) && !relay[0] && !relay[1] && !relay[3]){
				HR_Left();
				uhm.led2.On();
				uhm.led1.Off();
				uhm.led3.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[2] =true;
			}else
			if((RIGHT) && !relay[0] && !relay[1] && !relay[2]){
				HR_Right();
				uhm.led3.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[3] =true;
			}else
				/*
			if((wheel.flag[4]) && !relay[1] && !relay[2] && !relay[3]){
				HR_For();
				uhm.led1.On();
				uhm.led3.On();
				uhm.led2.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[0] =true;
			}else
			if((wheel.flag[5]) && !relay[1] && !relay[2] && !relay[3]){
				HR_For();
				uhm.led1.On();
				uhm.led2.On();
				uhm.led3.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[0] =true;
			}else
			if((wheel.flag[6]) && !relay[0] && !relay[2] && !relay[3]){
				HR_Back();
				uhm.led3.On();
				uhm.led4.On();
				uhm.led2.Off();
				uhm.led1.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[1] =true;
			}else
			if((wheel.flag[7]) && !relay[0] && !relay[2] && !relay[3]){
				HR_Back();
				uhm.led2.On();
				uhm.led4.On();
				uhm.led1.Off();
				uhm.led3.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[1] =true;
			}else
			if((con.MARU) && !relay[0] && !relay[1] && !relay[2] && !relay[3]){
				HR_Rcir();
				uhm.led2.On();
				uhm.led4.On();
				uhm.led1.Off();
				uhm.led3.Off();
				HR_Setpwm(0.9,0.9,0.9,0.9);
			}else
			if((con.BATSU) && !relay[0] && !relay[1] && !relay[2] && !relay[3]){
				HR_Lcir();
				uhm.led2.On();
				uhm.led4.On();
				uhm.led1.Off();
				uhm.led3.Off();
				HR_Setpwm(0.9,0.9,0.9,0.9);
			}else*/
			{
				HR_Stop();
				HR_Setpwm(0,0,0,0);
				relay[0]=false;
				relay[1]=false;
				relay[2]=false;
				relay[3]=false;
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led3.Off();
				uhm.led4.Off();
			}
			if(mode1 == 1 && mode2 == 1 && mode3 == 1 && mode4 == 1){
			}
			else{
				if(fall.flag[0]){
					for(i=0;i<5;i++){
						HR_For();
						Milli.delay(5);
						HR_Stop();
						Milli.delay(15);
					}
				}
				if(fall.flag[1]){
					for(i=0;i<5;i++){
						HR_Back();
						Milli.delay(5);
						HR_Stop();
						Milli.delay(15);
					}
				}if(fall.flag[2]){
					for(i=0;i<5;i++){
						HR_Left();
						Milli.delay(5);
						HR_Stop();
						Milli.delay(15);
					}
				}
				if(fall.flag[3]){
					for(i=0;i<5;i++){
						HR_Right();
						Milli.delay(5);
						HR_Stop();
						Milli.delay(15);
					}
				}
			}
		/*Fan*/
			//ファンに関しては昔のものを流用(4/10)
			if( R1 && (S_R1==false) ){
				uhm.communication.Fan1_Up();
				uhm.led1.Toggle();
			}
			S_R1 = R1;
			if( R2 && (S_R2==false) ){
				uhm.communication.Fan1_Down();
				uhm.led1.Toggle();
			}
			S_R2 = R2;
			/*open*/
			if( L2 && (S_L2==false) ){
				uhm.communication.Fan_open();
				uhm.led1.Toggle();
			}
			S_L2 = L2;
			/*open*/
			if( L1 && (S_L1==false) ){
				uhm.communication.sig2PIC();
				uhm.led1.Toggle();
			}
			S_L1 = L1;
		/*pole*/
			uhm.pole_state = uhm.communication.Pole_In();
			if( uhm.pole_state && uhm.pole_save ==false){
				uhm.pole_count++;
				if( uhm.pole_count==2 ){
					uhm.communication.sig2PIC();
				}
			}
			else{
			}
			uhm.pole_save = uhm.pole_state;
		/*mode check*/
		}else{
			HR_Stop();
			HR_Setpwm(0,0,0,0);
			relay[0]=false;
			relay[1]=false;
			relay[2]=false;
			relay[3]=false;
			uhm.led1.Off();
			uhm.led2.Off();
			uhm.led3.Off();
			uhm.led4.Off();
		}
	/* Encoder */
		Enc1 = uhm.encoders.getCounter1();
		Enc2 = uhm.encoders.getCounter2();
		Enc3 = uhm.encoders.getCounter3();
		Enc4 = uhm.encoders.getCounter4();
	/* Odometry */
	/* Mode */
		mode1 = (uhm.mode1.input_pin(true) & 0b00000111);
		mode2 = (uhm.mode2.input_pin(true) & 0b00000111);
		mode3 = (uhm.mode3.input_pin(true) & 0b00000111);
		mode4 = (uhm.mode4.input_pin(true) & 0b00000111);

	/* delay */
		Milli.delay(10);
	}
}
/* End Of File ---------------------------------------------------------------*/
