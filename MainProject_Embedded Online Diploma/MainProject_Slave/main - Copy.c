/*
* MainProject.c
*
* Created: 10/9/2023 1:44:16 AM
* Author : Mohammed Khalaf
*/
#include "Utils.h"
#include "MemoryMap.h"
#include "stdTypes.h"
#include "SegmentDisplay.h"
#include "DIO_interface.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

extern u8 hexPatterns[];
extern u8 segmentPatterns[];


u8 patterns[] = {
	0b00000001,
	0b00011110,
	0b00000010,
	0b00011101,
	0b00000100,
	0b00011011,
	0b00001000,
	0b00010111
};

#define RED_LED   PINB0
#define RED_GREEN PINB1

int main(void)
{
	init();
	DDRB = 0; // Set PORTB as input
	//PORTB = 0XFF;
	//DDRD = 0XFF;
	DDRD = 0; // Set PORTD as input
	PORTD = 0xFF; // Enable pull-up resistors on PORTD
	DDRA = 0XFF;
	
	/************************************************************************/
	/* Layer Architecture:                                                                     */
	/************************************************************************/
	//DIO_initPin(PC, 7 , OUTPUT);
	//DIO_initPin(PA , 5 , INFREE);
	
	u8 stopwatchRunning = 0; // Flag to indicate if the stopwatch is running
	u8 stopwatchValue = 30;   // Stopwatch value (in seconds)
	u8 press = 0;
	
	//DIO_initPin1(RED_LED , INPULL);
	//  DIO_initPin1(RED_GREEN , INPULL);
	
	while (1)
	{
		//segment_Display_MUX:
		/*PORTC = hexPatterns[3];
		SET_BIT(PORTD , 6); // This pin need to be off
		CLEAR_BIT(PORTD , 7);
		_delay_ms(300);
		PORTC = hexPatterns[12];
		SET_BIT(PORTB , 7); // This pin need to be off
		CLEAR_BIT(PORTB , 6);
		_delay_ms(300);*/
		
		/*for (u16 i = 0; i < 50 ; i++)
		{
		segment_Display_MLX(Value);
		//displayHexDigit_kit(Value);
		//segment_Display_MLX_kit(Value);
		}
		
		Value++;
		if(Value == 100)
		Value = 0;*/
		
		
		/*
		//segment_Display_BCD(Value);
		displayHexDigit_BCD(Value);
		_delay_ms(500);
		Value++;*/
		
		// Control 8-led 5 Pins:
		
		/*for (u8 i = 0; i < 8; i++)
		{
		CLEAR_BIT(PORTA, 4);
		PORTA = patterns[i];
		_delay_ms(300);
		SET_BIT(PORTA, 4);
		}*/
		
		/*for (u16 i = 0; i < 50 ; i++)
		{
		//segment_Display_MLX(Value);
		segment_Display_MLX_MultiDigits(Value);
		}
		Value++;*/
		
		// Motor Drive H-Bridge:
		/*SET_BIT(PORTD , 6);
		CLEAR_BIT(PORTD , 7);
		_delay_ms(10000);
		//Reverse Direction
		SET_BIT(PORTD , 7);
		CLEAR_BIT(PORTD , 6);
		_delay_ms(10000);
		//Stop motor
		CLEAR_BIT(PORTD , 6);
		CLEAR_BIT(PORTD , 7);
		_delay_ms(1500);*/
		
		//Layer Architecture:
		/*if (DIO_ReadPin(PA , 4) == HIGH)
		{
		
		}*/
		
		//Stop Watch Project:
		
		for (u16 i = 0; i < 25 ; i++)
		{
			segment_Display_MLX_kit(stopwatchValue);
		}
		
		if(!GET_BIT(PIND , 2))
		{
			
			if(press == 0)
			{
				press = 1;
				if (stopwatchRunning == 0)
				{
					stopwatchRunning = 1;
				}
				else
				{
					stopwatchRunning = 0;
				}
				//_delay_ms(5);  // Add a delay to debounce the button
				while(!GET_BIT(PIND , 2));
				_delay_ms(20);
			}
		}
		else
		{
			press = 0;
		}
		if (stopwatchRunning == 1)
		{
			stopwatchValue--;
			if (stopwatchValue == 0)
			{
				stopwatchValue = 30;
				stopwatchRunning = 0;
			}
		}
		if (stopwatchRunning == 0) // at the second time press
		{
			segment_Display_MLX_kit(stopwatchValue);
		}
		if (!GET_BIT(PIND , 3))
		{
			if (press == 0)
			{
				press = 1;
				stopwatchValue = 30; // Reset Stop watch
				//_delay_ms(1);  // Add a delay to debounce the button
				while(!GET_BIT(PIND , 3));
				_delay_ms(20);
			}
		}
		else
		{
			press = 0;
		}
		if(stopwatchRunning == 0 && !GET_BIT(PIND , 4))
		{
			stopwatchValue = stopwatchValue + 10;
			if (stopwatchValue > 100)
			{
				stopwatchValue = stopwatchValue % 100;
			}
			while(!GET_BIT(PIND , 4));
			
		}
		/*DIO_WritePin1(RED_LED , HIGH);
		_delay_ms(1000);
		DIO_WritePin1(RED_LED , LOW);
		_delay_ms(1000);
		*/
	}
	return 0;
}
