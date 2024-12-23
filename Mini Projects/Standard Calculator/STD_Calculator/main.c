/*
* STD_Calculator.c
*
* Created: 11/2/2023 1:36:02 AM
* Author : Mohammed Khalaf
*/
#include "stdTypes.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "LCD_int.h"

#include "LCD_Private.h"

#include "KEYPAD_int.h"
#include "AppFunctions.h"
#define F_CPU 8000000UL
#include <util/delay.h>

s16 num1 , num2;
int main(void)
{
	DIO_init();
	LCD_Init();
	LCD_SetCursor(1,1);
	LCD_WriteStr((u8*)" Welcome to STD");
	LCD_SetCursor(2,1);
	LCD_WriteStr((u8*)"   Calculator  ");
	_delay_ms(1000);
	LCD_Clear();
	delay();
	_delay_ms(500);
	LCD_Clear();
	u8 cell = 0 , keyValue ,operator;
	s32 result= 0;
	
	while (1)
	{
		operator = 0;
		result = 0;
		cell = 0;
		num1 = 0;
		num2 = 0;
		// Get the first number
		while(1)
		{
			keyValue = KEYPAD_GetKey();
			if (keyValue == 'C')
			{
				operator = 0;
				result = 0;
				cell = 0;
				num1 = 0;
				num2 = 0;
				LCD_Clear();
			}
			else if (keyValue == '+' || keyValue == '-' || keyValue == '*' || keyValue == '/')
			{
				operator = keyValue;
				LCD_SetCursor(1,cell+1);
				LCD_WriteChar(keyValue);
				break;
			}
			else if (keyValue != NO_KEY && keyValue >= '0' && keyValue <= '9')
			{
				num1 = num1*10 + (keyValue - '0');
				LCD_SetCursor(1,cell+1);
				LCD_WriteChar(keyValue);
				cell++;
			}
		}
		// Get the second number
		if (keyValue == operator)
		{
			cell = cell + 1;
		}
		while(1)
		{
			keyValue = KEYPAD_GetKey();
			if (keyValue == 'C')
			{
				operator = 0;
				result = 0;
				cell = 0;
				num1 = 0;
				num2 = 0;
				LCD_Clear();
			}
			else if (keyValue != NO_KEY && keyValue >= '0' && keyValue <= '9')
			{
				LCD_SetCursor(1,cell+1);
				LCD_WriteChar(keyValue);
				num2 = num2*10 + (keyValue - '0');
				cell++;
			}
			else if (keyValue == '=')
			{
				LCD_WriteChar(keyValue);
				break;
			}
		}
		// Select the operation:
		switch(operator)
		{
			case '+':
			result = sum(num1 , num2);
			break;
			
			case '-':
			result = sub(num1 , num2);
			break;
			
			case '*':
			result = multiplication(num1 , num2);
			break;
			
			case '/':
			result = division(num1 , num2);
			break;
		}
		LCD_WriteNumber(result);
	}
	
	return 0;
}