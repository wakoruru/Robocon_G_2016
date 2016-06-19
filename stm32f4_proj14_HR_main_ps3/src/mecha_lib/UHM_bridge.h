/* Config --------------------------------------------------------------------*/
#include "config/stm32plus.h"
#include "config/timing.h"
#include "config/timer.h"
#include "config/gpio.h"
#include "config/i2c.h"
/* Device --------------------------------------------------------------------*/
#include "devices/led.h"
#include "devices/button.h"
#include "devices/mpu6050.h"
/* mecha_lib -----------------------------------------------------------------*/
#include "mecha_lib/Motor_H.h"		// H_bridge_motor_driver
#include "mecha_lib/RS405CB.h"		// RS405CB_driver
#include "mecha_lib/buzzer.h"		// buzzer_driver
/* Ros -----------------------------------------------------------------------*/
#include "ros.h"
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Point.h>
#include <HR_2016/omni.h>