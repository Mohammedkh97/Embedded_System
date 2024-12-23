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

static volatile u8 Flag;
volatile u16 t1 , t2;

static volatile u8 counter, avgCounter = 0;
u16 distance , distanceBuffer[4] , avgDistance[10];


int main(void)
{
	systemInit();
	//Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	//Timer1_ICU_SetCallBack(InputCaptureFunction);
	//Timer1_InputCaptureEdge(RISING);

	//LCD_Goto_WriteString(1,1,(u8*)"US1 = ");
	while (1)
	{
		//LCD_Goto_WriteString(1,1,(u8*)"US1 = ");
		distance = Ultrasonic_Get_Distance(ULTRASONIC_1);
		LCD_Goto_WriteNumber(1,12,distance);
		_delay_ms(100);
		Flag = 0;
		TCNT1 = 0;
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		
		DIO_WritePin1(PIND5,HIGH);
		_delay_us(10);
		DIO_WritePin1(PIND5 , LOW);
		while(Flag < 2);
		u16 time = t2 - t1;
		distance = time / 58;
		LCD_Goto_WriteString(1,1,(u8*)"US1 = ");
		LCD_Goto_WriteNumber(1,13,distance);
		distanceBuffer[counter] = distance;
		counter++;
		
		if (counter == 4)
		{
			counter = 0;
			avgDistance[avgCounter] = distanceBuffer[counter];
			avgCounter++;
			
		}

	}
}
