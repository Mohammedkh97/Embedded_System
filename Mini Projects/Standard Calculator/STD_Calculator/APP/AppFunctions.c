/*
* AppFunctions.c
*
* Created: 11/2/2023 2:16:24 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "LCD_int.h"
#define F_CPU 8000000UL
#include <util/delay.h>


/*s16 sum(s8 *arr1 , s8 *arr2 , u8 size1 , u8 size2)
{
	s16 res = 0;
	s16 firstNum = 0;
	s16 secondNum = 0;
	
	for (u8 i = 0 ; i < size1 ; i++)
	{
		firstNum = firstNum * 10 + arr1[i];	// 1 , 2 , 3 ===> 123
	}
	for (u8 i = 0 ; i < size2; i++)
	{
		secondNum = secondNum * 10 + arr2[i];
	}
	res = firstNum + secondNum;
	
	return res;
}*/

s32 sum(s16 num1 , s16 num2)
{
	return num1 + num2;
}
/*s16 sub(s8 *arr1 , s8 *arr2 , u8 size1 , u8 size2)
{
	s16 res = 0;
	s16 firstNum = 0;
	s16 secondNum = 0;
	
	for (u8 i = 0 ; i < size1 ; i++)
	{
		firstNum = firstNum * 10 + arr1[i];
	}
	for (u8 i = 0 ; i < size2; i++)
	{
		secondNum = secondNum * 10 + arr2[i];
	}
	res = firstNum - secondNum;
	
	return res;
}*/

s32 sub(s16 num1 , s16 num2)
{
	return num1 - num2;
}
/*s32 multiplication(s8 *arr1 , s8 *arr2 , u8 size1 , u8 size2)
{
	s32 res = 0;
	s32 firstNum = 0;
	s32 secondNum = 0;
	
	for (u8 i = 0 ; i < size1 ; i++)
	{
		firstNum = firstNum * 10 + arr1[i];
	}
	for (u8 i = 0 ; i < size2; i++)
	{
		secondNum = secondNum * 10 + arr2[i];
	}
	res = firstNum * secondNum;
	
	return res;
}*/

s32 multiplication(s16 num1 , s16 num2)
{
	s32 res = num1 * num2;
	return  res;
}


/*s16 division(s8 *arr1 , s8 *arr2 , u8 size1 , u8 size2)
{
	s16 res = 0;
	s16 firstNum = 0;
	s16 secondNum = 0;
	
	if (size2 == 0)
	{
		LCD_Clear();
		LCD_SetCursor(1, 5);
		LCD_WriteStr((u8*)"Error");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Re-enter numbers again");
		return 0;
	}
	else
	{
		for (u8 i = 0 ; i < size1 ; i++)
		{
			firstNum = firstNum * 10 + arr1[i];
		}
		for (u8 i = 0 ; i < size2; i++)
		{
			secondNum = secondNum * 10 + arr2[i];
		}
		
	}
	res = firstNum / secondNum;
	return res;
}*/

s16 division(s16 num1 , s16 num2)
{
	if (num2 == 0)
	{
		LCD_Clear();
		LCD_SetCursor(1, 5);
		LCD_WriteStr((u8*)"Error");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Re-enter numbers again");
		return "invalid";
	}
	else
	{
		return num1 / num2;
	}
}

void delay()
{
	u8 numDots = 8; // Number of dots in the loading animation
	LCD_WriteStr((u8*) "Loading");
	for (u8 i = 0; i < numDots; i++)
	{
		LCD_WriteChar('.');
		_delay_ms(200);
	}
	LCD_SetCursor(2,1);
	LCD_WriteStr((u8*)"You Can Start");
}

