/*
* AppFunctions.c
*
* Created: 11/7/2023 12:09:55 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "AppFunctions.h"

#define F_CPU 8000000UL
#include <util/delay.h>
// Function to convert decimal to binary
void decimalToBinary(u32 Num) {
	if (Num == 0)
	{
		LCD_WriteChar(0);
		return;
	}
	u32 binary[32]; // Assuming 32-bit representation
	u8 i = 0;
	while (Num > 0)
	{
		binary[i] = Num % 2;
		Num /= 2;
		i++;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		LCD_WriteNumber(binary[j]);
	}
}

void decimalToHex(s32 num)
{
	// 0001 0001 = 1 1 == 17
	
	s8 LN = num % 16;
	s8 HN = num / 16;
	if (HN<10)
	{
		LCD_WriteChar(HN +'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}
	if (LN<10)
	{
		LCD_WriteChar(LN +'0');
	}
	else
	{
		LCD_WriteChar(LN+'A'-10);
	}
	
}


s32 binaryToDecimal(u8* binary)
{
	u8 length = string_len((u8*)binary);
	s32 res = 0;
	s16 weight = 1;
	for (s8 i = length - 1 ; i>= 0 ; i--)
	{
		if (binary[i]=='1')
		{
			res = res + weight;
		}
		weight = weight*2;
	}
	return res;
}

void binaryToHex(u8* binary)
{
	s32 decimal = binaryToDecimal((u8*)binary);
	decimalToHex(decimal);
}

u32 HexToDecimal(u8 hexChar)
{
	if (hexChar >= '0' && hexChar <= '9')
	{
		return hexChar - '0';
	}
	else if (hexChar >= 'A' && hexChar <= 'F')
	{
		return hexChar - 'A' + 10;
	}
	else if (hexChar >= 'a' && hexChar <= 'f')
	{
		return hexChar - 'a' + 10;
	} 
	else 
	{
		// Invalid hexadecimal character
		return -1;
	}
}

s32 HexStringToDecimal(u8* hexString)
{
	s32 result = 0;
	u8 length = string_len(hexString);

	for (s8 i = 0; i < length; i++)
	{
		s32 hexValue = HexToDecimal(hexString[i]);

		if (hexValue == -1)
		{
			// Invalid hexadecimal character
			LCD_WriteStr((u8*)"Invalid char");
			return -1;
		}

		result = result * 16 + hexValue;
	}

	return result;
}

void delay(u8 seconds)
{
	u8 numDots = 8; // Number of dots in the loading animation
	LCD_WriteStr((u8*) "Loading");
	for (u8 i = 0; i < numDots; i++)
	{
		LCD_WriteChar('.');
		_delay_ms(200);
	}
	LCD_SetCursor(2,1);
	LCD_WriteStr((u8*)"  Start Now");
}

