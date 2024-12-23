/*
* Ultrasoinc.c
*
* Created: 12/13/2023 1:08:28 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"
#include "Ultrasoinc.h"
#include "Ultrasonic_Config.h"

#define  F_CPU 8000000
#include <util/delay.h>

static volatile u8 flag;
static volatile u16 t1 , t2;

static void InputCaptureFunction();

void Ultrasonic_init()
{
	Timer1_Init(TIMER1_NORMAL_MODE , TIMER1_SCALER_8);
	Timer1_ICU_SetCallBack(InputCaptureFunction);
	Timer1_ICU_InterruptEnable();
}

u8 Ultrasonic_Get_Distance(Ultrasonic_Trigger_t US1)
{
	u8 distance = 0;
	u16 time = 0;

	flag = 0;
	TCNT1 = 0;
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	DIO_WritePin1(US1 , HIGH);
	_delay_us(10);
	DIO_WritePin1(US1 , LOW);
	while(flag < 2);
	time = t2 - t1;
	distance = time / 58;
	
	return distance;
}


static void InputCaptureFunction()
{
	if (flag == 0)
	{
		t1 = ICR1;
		flag = 1;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		flag = 2;
		Timer1_ICU_InterruptDisable();
		Timer1_InputCaptureEdge(RISING);
	}
	
}