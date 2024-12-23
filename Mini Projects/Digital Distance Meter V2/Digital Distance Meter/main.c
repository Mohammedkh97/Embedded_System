/*
* Digital Distance Meter.c
*
* Created: 4/8/2024 2:20:19 PM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "ADC_int.h"

#include "SegmentDisplay.h"
#include "MOTOR_Interface.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"
#include "Sensors_int.h"

#include "Ex_int.h"
#include "SERVO_int.h"
#include "Timers.h"
#include "Ultrasoinc.h"
#include "Ultrasonic_Config.h"
#include "UART.h"

#include "Application_File.h"


#define F_CPU 8000000UL
#include <util/delay.h>

static volatile u8 flag;
volatile u16 t1 , t2;




int main(void)
{
	systemInit();
	
	while (1)
	{
		systemRunnable();
	}
}

