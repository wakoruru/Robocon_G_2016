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
/* Ros -----------------------------------------------------------------------*/
#include "ros.h"
#include <HR_2016/controller.h>
#include <HR_2016/omni.h>
#include <HR_2016/odometry.h>
/* Macro ---------------------------------------------------------------------*/

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
void omni_cb(const HR_2016::omni& omni_msg){
	wheel.rate = omni_msg.rate;
	wheel.theta = omni_msg.M1_out;
	con.UP 		= omni_msg.UP;
	con.DOWN 	= omni_msg.DOWN;
	con.LEFT 	= omni_msg.LEFT;
	con.RIGHT	= omni_msg.RIGHT;
	con.MARU 	= omni_msg.MARU;
	con.BATSU 	= omni_msg.BATSU;
	con.SANKAKU = omni_msg.SANKAKU;
	con.SHIKAKU = omni_msg.SHIKAKU;
	con.R1		= omni_msg.R1;
	con.R2		= omni_msg.R2;
	con.R3		= omni_msg.R3;
	con.L1		= omni_msg.L1;
	con.L2		= omni_msg.L2;
	con.L3		= omni_msg.L3;
	con.SELECT	= omni_msg.SELECT;
	con.START	= omni_msg.START;
	con.ANALOG	= omni_msg.ANALOG;
	if( (con.UP&&!con.RIGHT&&!con.LEFT&&!con.DOWN) || (wheel.theta>=67.5 && wheel.theta<=112.5) ){//↑
		wheel.flag[0]=true;
		if((con.UP&&!con.RIGHT&&!con.LEFT&&!con.DOWN))wheel.rate=0.95*0.707;
	}else{
		wheel.flag[0]=false;
	}
	if( (!con.UP&&!con.RIGHT&&!con.LEFT&&con.DOWN) || (wheel.theta>=247.5 && wheel.theta<=292.5)){//↓
		wheel.flag[1]=true;
		if((!con.UP&&!con.RIGHT&&!con.LEFT&&con.DOWN))wheel.rate=0.95*0.707;
	}else{
		wheel.flag[1]=false;
	}
	if( (!con.UP&&!con.RIGHT&&con.LEFT&&!con.DOWN) || (wheel.theta>=0 && wheel.theta<=22.5) || (wheel.theta>=337.5 && wheel.theta<360) ){//←
		wheel.flag[2]=true;
		if((!con.UP&&!con.RIGHT&&con.LEFT&&!con.DOWN))wheel.rate=0.95*0.707;
	}else{
		wheel.flag[2]=false;
	}
	if( (!con.UP&&con.RIGHT&&!con.LEFT&&!con.DOWN) || (wheel.theta>=157.5 && wheel.theta<=202.5) ){//→
		wheel.flag[3]=true;
		if((!con.UP&&con.RIGHT&&!con.LEFT&&!con.DOWN))wheel.rate=0.95*0.707;
	}else{
		wheel.flag[3]=false;
	}
	if( wheel.theta>112.5 && wheel.theta<157.5 ){//↑→
		wheel.flag[4]=true;
	}else{
		wheel.flag[4]=false;
	}
	if( wheel.theta>22.5 && wheel.theta<67.5 ){//←↑
		wheel.flag[5]=true;
	}else{
		wheel.flag[5]=false;
	}
	if( wheel.theta>202.5 && wheel.theta<247.5 ){//↓→
		wheel.flag[6]=true;
	}else{
		wheel.flag[6]=false;
	}
	if( wheel.theta>292.5 && wheel.theta<337.5 ){//←↓
		wheel.flag[7]=true;
	}else{
		wheel.flag[7]=false;
	}
	if(wheel.rate==0){
		wheel.flag[0]=false;
		wheel.flag[1]=false;
		wheel.flag[2]=false;
		wheel.flag[3]=false;
		wheel.flag[4]=false;
		wheel.flag[5]=false;
		wheel.flag[6]=false;
		wheel.flag[7]=false;
	}
	if( con.ANALOG && (before.ANALOG==false) ){
		if(SAFE == false)SAFE=true;
		else SAFE=false;
	}
	before.ANALOG = con.ANALOG;
}
/* Main ----------------------------------------------------------------------*/
int main(void){
/*Valuable*/
	int i;
	uint8_t mode1=0,mode2=0,mode3=0,mode4=0;
	uint32_t Enc1=0,Enc2=0,Enc3=0,Enc4=0;
	float pwmval[4]={0,0,0,0};
	bool relay[4]={false,false,false,false};
	bool S_R1=false,S_R2=false,S_L1=false,S_L2=false;
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
/* ROS */
	ros::NodeHandle nh;
	HR_2016::odometry odometry;
	//ros::Subscriber<HR_2016::controller> cont("ps3con", &ps3_cb);
	ros::Subscriber<HR_2016::omni> omniwheel("omni_corrected", &omni_cb);
	ros::Publisher odom("odometry",&odometry);
	nh.initNode();
	//nh.subscribe(cont);
	nh.subscribe(omniwheel);
	nh.advertise(odom);
/*Loop*/
	while(1){
		if(SAFE){
			if( wheel.flag[0]==false && (bwhe.flag[0]==true) ){
				fall.flag[0]=true;
			}else{
				fall.flag[0]=false;
			}
			bwhe.flag[0] = wheel.flag[0];

			if( wheel.flag[1]==false && (bwhe.flag[1]==true) ){
				fall.flag[1]=true;
			}else{
				fall.flag[1]=false;
			}
			bwhe.flag[1] = wheel.flag[1];

			if( wheel.flag[2]==false && (bwhe.flag[2]==true) ){
				fall.flag[2]=true;
			}else{
				fall.flag[2]=false;
			}
			bwhe.flag[2] = wheel.flag[2];

			if( wheel.flag[3]==false && (bwhe.flag[3]==true) ){
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
				if(con.DOWN==1){
					uhm.motor2.Backward();
					uhm.motor4.Backward();
				}else
				if(con.UP==1){
					uhm.motor2.Forward();
					uhm.motor4.Forward();
				}

				if(con.BATSU==1){
					uhm.motor1.Forward();
					uhm.motor3.Forward();
				}else
				if(con.SANKAKU==1){
					uhm.motor1.Backward();
					uhm.motor3.Backward();
				}

				if(con.LEFT==1 || con.SHIKAKU==1){
					HR_Left();
				}else
				if(con.MARU==1 || con.RIGHT==1){
					HR_Right();
				}

				if(con.UP==0 && con.SANKAKU==0 && con.DOWN==0 && con.BATSU==0 && con.MARU==0 && con.RIGHT==0 && con.LEFT==0 && con.SHIKAKU==0){
					HR_Stop();
				}else{
					HR_Setpwm(0.95,0.95,0.95,0.95);
				}
			}
			else if((wheel.flag[0]) && !relay[1] && !relay[2] && !relay[3]){
				HR_For();
				uhm.led1.On();
				uhm.led2.Off();
				uhm.led3.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[0] =true;
			}else
			if((wheel.flag[1]) && !relay[0] && !relay[2] && !relay[3]){
				HR_Back();
				uhm.led4.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led3.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[1] =true;
			}else
			if((wheel.flag[2]) && !relay[0] && !relay[1] && !relay[3]){
				HR_Left();
				uhm.led2.On();
				uhm.led1.Off();
				uhm.led3.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[2] =true;
			}else
			if((wheel.flag[3]) && !relay[0] && !relay[1] && !relay[2]){
				HR_Right();
				uhm.led3.On();
				uhm.led1.Off();
				uhm.led2.Off();
				uhm.led4.Off();
				HR_Setpwm(pwmval[0],pwmval[1],pwmval[2],pwmval[3]);
				relay[3] =true;
			}else
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
		/*Fan*/
			//ファンに関しては昔のものを流用(4/10)
			if( con.R1 && (S_R1==false) ){
				uhm.communication.Fan1_Up();
				uhm.led1.Toggle();
			}
			S_R1 = con.R1;
			if( con.R2 && (S_R2==false) ){
				uhm.communication.Fan1_Down();
				uhm.led1.Toggle();
			}
			S_R2 = con.R2;
			/*open*/
			if( con.L2 && (S_L2==false) ){
				uhm.communication.Fan_open();
				uhm.led1.Toggle();
			}
			S_L2 = con.L2;
			/*open*/
			if( con.L1 && (S_L1==false) ){
				uhm.communication.sig2PIC();
				uhm.led1.Toggle();
			}
			S_L1 = con.L1;
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
		odometry.x = 0;
		odometry.y = 0;
		odometry.z = 0;
		odometry.w = 0;
	/* Mode */
		mode1 = (uhm.mode1.input_pin(true) & 0b00000111);
		mode2 = (uhm.mode2.input_pin(true) & 0b00000111);
		mode3 = (uhm.mode3.input_pin(true) & 0b00000111);
		mode4 = (uhm.mode4.input_pin(true) & 0b00000111);
		odometry.mode1 = mode1;
		odometry.mode2 = mode2;
		odometry.mode3 = mode3;
		odometry.mode4 = mode4;
	/* ros */
		odom.publish(&odometry);
		nh.spinOnce();
	/* delay */
		Milli.delay(10);
	}
}
/* End Of File ---------------------------------------------------------------*/
