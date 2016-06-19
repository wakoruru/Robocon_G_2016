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
ps3 con;
omn wheel;
void omni_cb(const HR_2016::omni& omni_msg){
	wheel.rate = omni_msg.rate;
	wheel.M1_out = omni_msg.M1_out*omni_msg.rate;
	wheel.M2_out = omni_msg.M2_out*omni_msg.rate;
	wheel.M3_out = omni_msg.M3_out*omni_msg.rate;
	wheel.M4_out = omni_msg.M4_out*omni_msg.rate;
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
	if(wheel.M1_out>=0 && wheel.M2_out<=0 && wheel.M3_out<=0 && wheel.M4_out>=0){//-+-+
		wheel.flag[0]=true;
	}else{
		wheel.flag[0]=false;
	}
	if(wheel.M1_out<=0 && wheel.M2_out>=0 && wheel.M3_out>=0 && wheel.M4_out<=0){//+-+-
		wheel.flag[1]=true;
	}else{
		wheel.flag[1]=false;
	}
	if(wheel.M1_out>=0 && wheel.M2_out>=0 && wheel.M3_out<=0 && wheel.M4_out<=0){//++--
		wheel.flag[2]=true;
	}else{
		wheel.flag[2]=false;
	}
	if(wheel.M1_out<=0 && wheel.M2_out<=0 && wheel.M3_out>=0 && wheel.M4_out>=0){//--++
		wheel.flag[3]=true;
	}else{
		wheel.flag[3]=false;
	}
	if(wheel.M1_out==0 && wheel.M2_out==0 && wheel.M3_out==0 && wheel.M4_out==0){
		wheel.flag[0]=false;
		wheel.flag[1]=false;
		wheel.flag[2]=false;
		wheel.flag[3]=false;
	}
}
/* Main ----------------------------------------------------------------------*/
int main(void){
	/*Valuable*/
	uint32_t Enc1=0,Enc2=0,Enc3=0,Enc4=0;
	bool relay[4]={false,false,false,false};
	bool S_R1=false,S_R2=false;
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
		/* Enc read */
		Enc1=uhm.encoders.getSpeed1();
		Enc2=uhm.encoders.getSpeed2();
		Enc3=uhm.encoders.getSpeed3();
		Enc4=uhm.encoders.getSpeed4();
		/*
		Enc1=uhm.encoders.getCounter1();
		Enc2=uhm.encoders.getCounter2();
		Enc3=uhm.encoders.getCounter3();
		Enc4=uhm.encoders.getCounter4();
		*/
		/* odom */
		odometry.x = Enc1;
		odometry.y = Enc2;
		odometry.z = Enc3;
		odometry.w = Enc4;
		/* led */
		/*Motor*/
		//オムニっぽくしてみる(4/11)
		if(con.SHIKAKU && !relay[1] && !relay[2] && !relay[3]){
			HR_Lcir();
			HR_Setpwm(0.5,0.5,0.5,0.5);
			relay[0] =true;
		}else
		if(con.SANKAKU && !relay[1] && !relay[2] && !relay[3]){
			HR_Rcir();
			HR_Setpwm(0.5,0.5,0.5,0.5);
			relay[0] =true;
		}else
		if(con.UP && !relay[1] && !relay[2] && !relay[3]){
			HR_For();
			HR_Setpwm(1.0,1.0,1.0,1.0);
			relay[0] =true;
		}else
		if((wheel.flag[0]) && !relay[1] && !relay[2] && !relay[3]){
			HR_For();
			HR_Setpwm(wheel.M1_out,wheel.M2_out,wheel.M3_out,wheel.M4_out);
			relay[0] =true;
		}else
		if(con.DOWN && !relay[0] && !relay[2] && !relay[3]){
			HR_Back();
			HR_Setpwm(1.0,1.0,1.0,1.0);
			relay[1] =true;
		}else
		if((wheel.flag[1]) && !relay[0] && !relay[2] && !relay[3]){
			HR_Back();
			HR_Setpwm(wheel.M1_out,wheel.M2_out,wheel.M3_out,wheel.M4_out);
			relay[1] =true;
		}else
		if(con.RIGHT&& !relay[0] && !relay[1] && !relay[3]){
			HR_Right();
			HR_Setpwm(0.7,0.7,0.7,0.7);
			relay[2] =true;
		}else
		if((wheel.flag[2]) && !relay[0] && !relay[1] && !relay[3]){
			HR_Right();
			HR_Setpwm(wheel.M1_out,wheel.M2_out,wheel.M3_out,wheel.M4_out);
			relay[2] =true;
		}else
		if(con.LEFT && !relay[0] && !relay[1] && !relay[2]){
			HR_Left();
			HR_Setpwm(0.7,0.7,0.7,0.7);
			relay[3] =true;
		}else
		if((wheel.flag[3]) && !relay[0] && !relay[1] && !relay[2]){
			HR_Left();
			HR_Setpwm(wheel.M1_out,wheel.M2_out,wheel.M3_out,wheel.M4_out);
			relay[3] =true;
		}else
		{
			HR_Stop();
			HR_Setpwm(0,0,0,0);
			relay[0]=false;
			relay[1]=false;
			relay[2]=false;
			relay[3]=false;
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
		/*mode check*/
		if(wheel.flag[0]||(uhm.mode1.input_pin(true) & 0b00000111) == 0b001 ){
			uhm.led1.On();
		}else{
			uhm.led1.Off();
		}
		if(wheel.flag[1]||(uhm.mode2.input_pin(true) & 0b00000111) == 0b001 ){
			uhm.led2.On();
		}else{
			uhm.led2.Off();
		}
		if(wheel.flag[2]||(uhm.mode3.input_pin(true) & 0b00000111) == 0b001 ){
			uhm.led3.On();
		}else{
			uhm.led3.Off();
		}
		if(wheel.flag[3]||(uhm.mode4.input_pin(true) & 0b00000111) == 0b001 ){
			uhm.led4.On();
		}else{
			uhm.led4.Off();
		}
		/*mode*/
		odometry.mode1 = (uhm.mode1.input_pin(true) & 0b00000111);
		odometry.mode2 = (uhm.mode2.input_pin(true) & 0b00000111);
		odometry.mode3 = (uhm.mode3.input_pin(true) & 0b00000111);
		odometry.mode4 = (uhm.mode4.input_pin(true) & 0b00000111);
		/* ros */
		odom.publish(&odometry);
		nh.spinOnce();
		/* delay */
		Milli.delay(10);
	}
}
/* End Of File ---------------------------------------------------------------*/
