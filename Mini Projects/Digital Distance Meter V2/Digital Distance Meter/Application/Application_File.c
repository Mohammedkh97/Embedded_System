/*
* Application_File.c
*
* Created: 3/25/2024 1:12:12 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "Ex_int.h"
#include "Application_File.h"
#include "Ultrasoinc.h"

#define F_CPU 8000000UL
#include <util/delay.h>

static volatile u8 counter, bufferIndex = 0 , avgFlag = 0 , displayFlag = 0;
volatile u16 distance , Distance_Sum, distanceBuffer[4] = {0} , avgDistance;

u8 Cursor = 1;
void systemInit(void)
{
	//
	DIO_init();
	EXI_init();
	EXI_Enable(EX_INT0);
	LCD_Init();
	Ultrasonic_init();
	GLOBAL_ENABLE();
}
void systemRunnable()
{


	distance = Ultrasonic_Get_Distance(ULTRASONIC_1);
	distanceBuffer[bufferIndex] = distance;
	if (!displayFlag)
	{
		//While Measuring Distances, Laser is ON:
		DIO_WritePin1(PINC0 , HIGH);
		LCD_Goto_WriteString(1,1,(u8*)"Current Dist: ");
	}
	LCD_Goto_WriteNumber(2,Cursor,distanceBuffer[bufferIndex]);
	bufferIndex++;
	//Handle three, two or one digit number:
	if (distance >= 100)
	{
		Cursor = Cursor + 4;
	}
	else if (distance >= 10 && distance < 100)
	{
		Cursor = Cursor + 4;
		LCD_Goto_WriteCharacter(2,Cursor-2,' ');
	}
	else if (distance >= 0 && distance < 10)
	{
		Cursor = Cursor + 4;
		LCD_Goto_WriteCharacter(2,Cursor-3,' ');
	}
	
	if (Cursor >= 16)
	{
		Cursor = 1;
	}
	if (bufferIndex == 4)
	{
		bufferIndex = 0;
	}
	if (avgFlag)
	{
		if (avgDistance < 100)
		{
			LCD_Goto_WriteCharacter(1,15,' ');
		}
		if (avgDistance < 10)
		{
			LCD_Goto_WriteCharacter(1,14,' ');
		}
		avgFlag = 0;
		LCD_Goto_WriteString(1,1,(u8*)"AvgDistance =");
		LCD_Goto_WriteNumber(1,13,avgDistance);
		avgDistance = 0;
		displayFlag = 1;
	}
	_delay_ms(500);
}

ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
	//LCD_Clear();
	DIO_WritePin1(PINC0 , LOW);
	u8 counter;
	for ( counter = 0 ; counter < 4 ; counter++)
	{
		Distance_Sum = Distance_Sum + distanceBuffer[counter];
	}
	if (counter == 4)
	{
		avgDistance = Distance_Sum /4;
		avgFlag = 1;
	}
	for (u8 i = 0; i < 4; i++)
	{
		distanceBuffer[i] = 0;
	}
	Distance_Sum = 0;
}
