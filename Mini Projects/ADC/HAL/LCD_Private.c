/*
 * LCD_Private.c
 *
 * Created: 10/28/2023 9:51:37 PM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "LCD_Config.h"
#include "LCD_Private.h"
#include "Utils.h"
#include "LCD_int.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

u8 man[] = {
	0B00100,
	0B01010,
	0B00100,
	0B10101,
	0B11111,
	0B00100,
	0B01010,
	0B10001
};

u8 string_len(u8 *str)
{
	u8 i;
	for (i = 0; str[i]; i++)
	{
	}

	return i;
}
void reverseString(u8 *str)
{
	char temp;
	int length = string_len(str);
	for (int i = 0; i < length / 2; i++)
	{
		temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
	}
}

void intoString(s32 num, u8 *str)
{
	int rem = 0 , i = 0;
	// Corner case if the number is zero
	if (num == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return;
	}
	
	for (i = 0; num != 0; i++)
	{
		if (num < 0)
		{
			num = num * (-1);
			for (i = 0; num != 0; i++)
			{
				rem = num % 10;
				str[i] = rem + '0';
				num = num / 10;
			}
			str[i] = '-';
		}
		else
		{
			rem = num % 10;
			str[i] = rem + '0';
			num = num / 10;
		}
	}
	// printf("i = %d\n", i);
	str[i] = 0;
	reverseString(str);
}
void Dec_Bin(s32 num)
{
	u8 flag = 0;
	s32 i;
	for (i = 7; i >= 0; i--)
	{
		if ((num >> i) & 1)
		{
			flag = 1;
			LCD_WriteNumber(1);
		}
		else
		{
			if (flag == 1)
			LCD_WriteNumber(0);
		}
	}
}

void SnakeWord(u8* name)
{
	u8 i ;
	for (i = 1 ; i < string_len(name); i++)
	{
		LCD_WriteStr((u8*)name + string_len(name) - i);
		_delay_ms(10);
		LCD_Clear();
	}
	for (i = 1 ; i<=16 ; i++)
	{
		LCD_Clear();
		LCD_SetCursor(1,i);
		LCD_WriteStr((u8*)name);
		_delay_ms(10);
	}
	/*for (i = 16 ; i>=1 ; i--)
	{
		LCD_Clear();
		LCD_SetCursor(1,i);
		LCD_WriteStr((u8*)name);
		LCD_WriteStr("  ");
		//LCD_WriteChar(name[j]);
		_delay_ms(10);
	}*/
	for (i = 1 ; i < string_len(name); i++)
	{
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)name + string_len(name) - i);
		_delay_ms(10);
		LCD_Clear();
	}
	for (i = 1; i<=16; i++)
	{
		LCD_Clear();
		LCD_SetCursor(2,i);
		LCD_WriteStr((u8*)name);
		_delay_ms(10);
	}
}


// Here, you need to store the shape of this pattern in the memory of LCD.
void customChar(u8* pattern , u8 address)
{
	
	write_instruction(0x40 + address*8);
	for (u8 i = 0 ; i < 8 ; i++)
	{
		write_Data(pattern[i]);
		//LCD_WriteStr((u8*)man);
	}
	write_instruction(0x80);
}
