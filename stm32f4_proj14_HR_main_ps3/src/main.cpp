/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
/* config */
#include "config/stm32plus.h"
#include "config/gpio.h"
#include "config/timing.h"
#include "config/timer.h"
#include "config/usart.h"
//#include "config/adc.h"
/* board */
#include "board/f4discovery.h"
/* usb */
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"
#include "usbh_hid_ps3.h"
/* mecha_lib */
#include "mecha_lib/UHMwithF4dis_NMD.h"
//#include "mecha_lib/PSD.h"
/* namespace */
using namespace stm32plus;
/* Defines -------------------------------------------------------------------*/
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
#define S_L2		btn_state[8]
#define S_R2		btn_state[9]
#define S_L1		btn_state[10]
#define S_R1		btn_state[11]
#define S_SANKAKU	btn_state[12]
#define S_MARU		btn_state[13]
#define S_BATSU		btn_state[14]
#define S_SHIKAKU	btn_state[15]
#define S_ANALOG	btn_state[16]
/* Macro ---------------------------------------------------------------------*/

#define HR_Lcir()	uhm.motor1.Forward();  uhm.motor2.Forward();  uhm.motor3.Forward();  uhm.motor4.Forward()
#define HR_Rcir()	uhm.motor1.Backward(); uhm.motor2.Backward(); uhm.motor3.Backward(); uhm.motor4.Backward()
#define HR_For()	uhm.motor1.Backward(); uhm.motor2.Forward();  uhm.motor3.Backward(); uhm.motor4.Forward()
#define HR_Back()	uhm.motor1.Forward();  uhm.motor2.Backward(); uhm.motor3.Forward();  uhm.motor4.Backward()
#define HR_Left()	uhm.motor1.Forward(); uhm.motor2.Forward();  uhm.motor3.Backward(); uhm.motor4.Backward()
#define HR_Right()	uhm.motor1.Backward();  uhm.motor2.Backward(); uhm.motor3.Forward();  uhm.motor4.Forward()
#define HR_Setpwm(a,b,c,d)	uhm.motor1.Setpwm(a);   uhm.motor2.Setpwm(b);   uhm.motor3.Setpwm(c);   uhm.motor4.Setpwm(d)
#define HR_Stop()	uhm.motor1.Stop();     uhm.motor2.Stop();     uhm.motor3.Stop(); uhm.motor4.Stop();
/* Variables -----------------------------------------------------------------*/
USB_OTG_CORE_HANDLE           USB_OTG_Core_dev;
USBH_HOST                     USB_Host;
uint16_t btn[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool btn_state[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t fri[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
/* Constants -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/* Using ---------------------------------------------------------------------*/
/* Class ---------------------------------------------------------------------*/
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
omn wheel,bwhe,fall;
/*
 * used timers
 * timer1	: motor
 * timer2	: pc
 * timer3	: encoder
 * timer4	: encoder
 * timer5	:controller
 * timer6	:microsecondDelay
 * timer7	:
 * timer8	: motor
 * timer9	:
 * timer10	:
 * timer11	:
 * timer12	:
 */
int main(void)
{
/* Valuable */
	int i;
	uint8_t mode1=0,mode2=0,mode3=0,mode4=0;
	float pwmval[4]={0,0,0,0};
	bool relay[4]={false,false,false,false};
	float pwm1,pwm2;
	float left_x=0,left_y=0;
	float angle=0;
	float x=0.0,y=0.0;
	float theta=0.0;
	bool pole_state=0,pole_save=true;
	bool past_connect=false;
	uint8_t pole_count=0;
	int32_t Enc3=0,Enc4=0;
/* Init Host Library */
	USBH_Init(&USB_OTG_Core_dev, USB_OTG_FS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks );
/* NVIC */
	Nvic::initialise();
	UHM uhm;
/* Delay */
	MillisecondTimer Milli;
	Milli.initialise();
//*USBtimer*/
	USBTimer timer;
	while(1){
/* Manual */
		if( ps3_connected == 1 ){
			past_connect = true;
			uhm.led1.On();
			uhm.led3.Off();
	/* controller */
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
	/* main *//*Motor*/
			pwmval[0]=0.95;
			pwmval[1]=0.95;
			pwmval[2]=0.95;
			pwmval[3]=0.95;
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
			if((MARU) && !relay[0] && !relay[1] && !relay[2]){
				HR_Lcir();
				uhm.led3.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				//relay[3] =true;
			}else
			if((BATSU) && !relay[0] && !relay[1] && !relay[2]){
				HR_Rcir();
				uhm.led3.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				//relay[3] =true;
			}else
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
		/*fan 成功*/
			if( R1 && (S_R1==false) ){
				uhm.communication.Fan1_Up();
			}
			S_R1 = R1;
			if(R2 && (S_R2==false) ){
				uhm.communication.Fan1_Down();
			}
			S_R2 = R2;
			if(L2 && (S_L2==false) ){
				uhm.communication.Fan_open();
			}
			S_L2 = L2;
			/*open*/
			if( L1 && (S_L1==false) ){
				uhm.communication.sig2PIC();
				uhm.led1.Toggle();
			}
			S_L1 = L1;
		/*open*/
			if( SANKAKU && (S_SANKAKU==false) ){
				uhm.communication.Propera();
				uhm.led1.Toggle();
			}
			S_SANKAKU = SANKAKU;
		/*pole　成功*/
			/*
			pole_state = uhm.communication.Pole_In();
			if( pole_state && pole_save ==false){
				pole_count++;
				if( pole_count==2 ){
					uhm.led4.On();
					uhm.communication.sig2PIC();
				}
			}
			else{
				uhm.led4.Off();
			}
			pole_save = pole_state;
			*/
		}
/* Auto */
		if( past_connect == true && ps3_connected == 0 ){
			uhm.led1.Off();
			past_connect = false;//コントローラ確認
			while( pole_count != 0 && ps3_connected == 0 ){
				uhm.led3.On();
				HR_For();
				HR_Setpwm(0.8,0.8,0.8,0.8);
				pole_state = uhm.communication.Pole_In();
				if( pole_state && pole_save == false ){
					pole_count++;
					if( pole_count >= 2 ){
					/*motor*/
						HR_Stop();
					/*circuit*/
						uhm.led4.On();
						uhm.communication.sig2PIC();
					}
				}
				if(pole_count < 2){
				/* motor */

				}else{
					HR_Stop();
				}
				pole_save = pole_state;
			/*encoder*/

				//printf("encoder E3:%ld E4:%ld x:%f y:%f contoroller:%d\n", Enc3, Enc4, x, y, ps3_connected);
				//printf("pinstate %d %d %d %d \n",ps3_connected,pole_state, pole_count, cir.Output_state);
				Milli.delay(10);
			}
			uhm.led3.Off();
			HR_Stop();
		}
		/* debug*/
		#ifdef DEBUG_PORT
//			printf("Button state 0x%02x 0x%02x 0x%02x \n", HID_PS3_Data.button[0], HID_PS3_Data.button[1], HID_PS3_Data.button[2] );
//			printf("Analog state %03f %03f %03f %03d  \n", left_x, left_y, angle4, ps3_connected);
//			printf("Analog state %lf %lf %03d %03d \n",pwm1,pwm2,127 - HID_PS3_Data.analog_stick[3], HID_PS3_Data.analog_stick[3] - 127 );
//			printf("pinstate %d %d %d %d",ps3_connected,pole_state, pole_count, cir.Output_state);
//			printf("encoder %d %d",encoder_3.getCounter(),encoder_4.getCounter());
//			printf("Analog state ");
//			for( int i=0 ; i<12 ; i++ ) prin,tf("%02x ", HID_PS3_Data.button_analog[i]);
//			printf("\n");
//			printf("\n");
//		printf("OMRON 1:%2d 2:%2d 3:%2d 4:%2d 5:%2d 6:%2d \n",sensor1.input_pin(false),sensor2.input_pin(false),sensor3.input_pin(false),sensor4.input_pin(false),sensor5.input_pin(false),sensor6.input_pin(false));
		#endif
		Milli.delay(10);
	}
}
/* End Of File ---------------------------------------------------------------*/
