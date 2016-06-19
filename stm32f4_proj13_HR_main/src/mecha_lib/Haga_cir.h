#pragma once
namespace stm32plus{
	class Haga_cir{
	public:
		bool Pin1_state,Pin2_state,Output_state,Input_state;
		Haga_cir(const GpioPinRef& _Pin1,const GpioPinRef& _Pin2,const GpioPinRef& _Output,const GpioPinRef& _Input):Pin1(_Pin1),Pin2(_Pin2),Output(_Output),Input(_Input){
			Pin1_Off();
			Pin2_Off();
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
	private:
		GpioPinRef Pin1,Pin2,Output,Input;
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
	};
}
