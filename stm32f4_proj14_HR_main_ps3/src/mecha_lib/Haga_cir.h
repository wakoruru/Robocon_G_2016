#pragma once
namespace stm32plus{
	class Haga_cir{
	public:
		bool Pin0_state,Pin1_state,Pin2_state,Output_state,Out2_state,Input_state;
		Haga_cir(const GpioPinRef& _Pin0,const GpioPinRef& _Pin1,const GpioPinRef& _Pin2,const GpioPinRef& _Output,const GpioPinRef& _Input,const GpioPinRef& _Out2):Pin0(_Pin0),Pin1(_Pin1),Pin2(_Pin2),Output(_Output),Input(_Input),Out2(_Out2){
			Pin0_Off();
			Pin1_Off();
			Pin2_Off();
			Out2_On();
			Output_Off();
		}
	/* Fan1 */
		void Fan1_On(){
			Pin1_On();
			Pin2_Off();
		}
		void Fan1_Up(){
			Pin1_Toggle();
		}
		void Fan1_Down(){
			Pin2_Toggle();
		}
	/* Fan2 */
		void Fan2_On(){
			Pin1_On();
		}
		void Fan2_Off(){
			Pin1_Off();
		}
	/* Pole */
		bool Pole_In(){
			Input_state =( Input.read() == false);
			return Input_state;
		}
		void sig2PIC(){
			Output_Toggle();
		}
		void Fan_open(){
			Pin0_Toggle();
		}
		void Propera(){
			Out2_Toggle();
		}
	private:
		GpioPinRef Pin0,Pin1,Pin2,Output,Input,Out2;
	/* Pin1 */
		void Pin0_On(){
			Pin0.set();
			Pin0_state=true;
		}
		void Pin0_Off(){
			Pin0.reset();
			Pin0_state=false;
		}
		void Pin0_Toggle(){
			if(Pin0_state) 	Pin0_Off();
			else			Pin0_On();
		}
	/* Pin1 */
		void Pin1_On(){
			Pin1.set();
			Pin1_state=true;
		}
		void Pin1_Off(){
			Pin1.reset();
			Pin1_state=false;
		}
		void Pin1_Toggle(){
			if(Pin1_state) 	Pin1_Off();
			else			Pin1_On();
		}
	/* Pin2 */
		void Pin2_On(){
			Pin2.set();
			Pin2_state=true;
		}
		void Pin2_Off(){
			Pin2.reset();
			Pin2_state=false;
		}
		void Pin2_Toggle(){
			if(Pin2_state) 	Pin2_Off();
			else			Pin2_On();
		}
	/* Output */
		void Output_On(){
			Output.set();
			Output_state=true;
		}
		void Output_Off(){
			Output.reset();
			Output_state=false;
		}
		void Output_Toggle(){
			if(Output_state) Output_Off();
			else			 Output_On();
		}
	/* Output */
		void Out2_On(){
			Out2.set();
			Out2_state=true;
		}
		void Out2_Off(){
			Out2.reset();
			Out2_state=false;
		}
		void Out2_Toggle(){
			if(Out2_state) Out2_Off();
			else			 Out2_On();
		}
	};
}
