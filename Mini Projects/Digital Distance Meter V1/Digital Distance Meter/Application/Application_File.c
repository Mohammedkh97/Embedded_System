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
#include "Ultrasoinc.h"
#include "Application_File.h"
#include "Configuration.h"

#define F_CPU 8000000UL
#include <util/delay.h>

static u8 counter, bufferIndex = 0 , avgFlag = 1 , displayFlag = 0 , exitFlag = 0;
static volatile f32 distance , Distance_Sum, distanceBuffer[4] , avgDistance;
u8 reset = 0;
u8 Cursor = 1 , i = 1 ;
void systemInit(void)
{
	_delay_ms(1000);
	DIO_init();
	EXI_init();
	EXI_Enable(EX_INT0);
	LCD_Init();
	Ultrasonic_init();
	GLOBAL_ENABLE();
	reset = 0;
	
}
void systemRunnable()
{
	
	DIO_WritePin1(LASER_PIN , HIGH);
	distance = Ultrasonic_Get_Distance(ULTRASONIC_1);
	distanceBuffer[bufferIndex] = distance;
	//LCD_Goto_WriteNumber(2,Cursor,distanceBuffer[bufferIndex]);
	bufferIndex++;
	if (distance > MAX_RANGE)
	{
	
		LCD_Goto_WriteString(1,1,(u8*)"    Warning!    ");
		LCD_Goto_WriteString(2,1,(u8*)" Range Exceeded! ");
		exitFlag = 1;
	}
	if (distance <= MAX_RANGE && exitFlag == 1)
	{
		exitFlag = 0;
		LCD_Clear();
	}
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
	//LCD_Goto_WriteNumber(2,1,bufferIndex);
	if (bufferIndex == 4)
	{
		for ( counter = 0 ; counter < 4 ; counter++)
		{
			Distance_Sum = Distance_Sum + distanceBuffer[counter];
		}
		bufferIndex = 0;
	}
	if (counter == 4 && !exitFlag)
	{
		avgDistance = Distance_Sum /4;
		for (u8 i = 0; i < 4; i++)
		{
			distanceBuffer[i] = 0;
		}
		LCD_Goto_WriteString(1,1,(u8*)"Avg Dist = ");
		LCD_GoTo_WriteFloatNumber(1,12,avgDistance , 1);
		counter = 0;
	}
	
	if (avgDistance < 100)
	{
		LCD_Goto_WriteCharacter(1,16,' ');
	}
	if (avgDistance < 10)
	{
		LCD_Goto_WriteCharacter(1,15,' ');
	}
	while (!avgFlag)
	{
		LCD_Goto_WriteString(1,1,(u8*)"Selected Value: ");
		LCD_GoTo_WriteFloatNumber(2,6,avgDistance,1);
	}
	
	Distance_Sum = 0;
}

ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
	//LCD_Clear();
	DIO_WritePin1(LASER_PIN , LOW);
	avgFlag = 0;
}
