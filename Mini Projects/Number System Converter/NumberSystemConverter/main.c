/*
* NumberSystemConverter.c
*
* Created: 11/5/2023 1:17:15 PM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"

#include "LCD_int.h"
#include "LCD_Private.h"
#include "AppFunctions.h"

#include "KEYPAD_int.h"

#define F_CPU 8000000UL
#include <util/delay.h>


s32 num;
u8 binary[32];
u8 hexNum[8];

int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	LCD_Clear();
	LCD_SetCursor(1,3);
	LCD_WriteStr((u8*)" Welcome to");
	LCD_SetCursor(2,1);
	LCD_WriteStr((u8*)"NumSysCalculator");
	_delay_ms(1000);
	LCD_Clear();
	delay(4);
	_delay_ms(500);
	LCD_SetCursor(1,1);
	LCD_WriteStr((u8*)"1.D2B 2.D2H3.B2D");
	LCD_SetCursor(2,1);
	LCD_WriteStr((u8*)"4.B2H 5.H2D");
	u8 cell = 0 , keyValue  , size = 0 , length = 0 , lengthofHex = 0 /*, entryFlag = 0*/;
	/* Replace with your application code */
	while (1)
	{
		length = string_len((u8*)binary);
		lengthofHex = string_len((u8*)hexNum);
		while(1)
		{
			keyValue = KEYPAD_GetKey();
			if (keyValue == 'Q')
			{
				num = 0;
				cell = 0;
				LCD_Clear();
			}
			if (keyValue == '1') // Decimal To Binary
			{
				LCD_Clear();
				LCD_WriteStr((u8*)"Dec 2 Bin");
				_delay_ms(800);
				LCD_Clear();
				LCD_SetCursor(1,1);
				LCD_WriteStr((u8*)"DEC: ");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"BIN: ");
				num = 0;
				cell = 0;
				while(1)
				{
					keyValue = KEYPAD_GetKey();
					if (keyValue == 'Q')
					{
						num = 0;
						cell = 0;
						LCD_Clear();
					}
					if (keyValue != NO_KEY && keyValue >= '0' && keyValue <= '9')
					{
						num = num*10 + (keyValue - '0');
						LCD_SetCursor(1,cell+6);
						LCD_WriteChar(keyValue);
						size++;
						cell++;
					}
					else if (keyValue == '=')
					{
						//LCD_WriteChar(keyValue);
						LCD_SetCursor(2,6);
						break;
					}
				}
				decimalToBinary(num);
			}
			if (keyValue == '2')		// Decimal To Hex
			{
				LCD_Clear();
				LCD_WriteStr((u8*)"Dec 2 Hex");
				_delay_ms(800);
				LCD_Clear();
				LCD_SetCursor(1,1);
				LCD_WriteStr((u8*)"DEC: ");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"HEX: ");
				num = 0;
				cell = 0;
				while(1)
				{
					keyValue = KEYPAD_GetKey();
					if (keyValue == 'Q')
					{
						cell = 0;
						num = 0;
						LCD_Clear();
					}
					if (keyValue != NO_KEY && keyValue >= '0' && keyValue <= '9')
					{
						num = num*10 + (keyValue - '0');
						LCD_SetCursor(1,cell+6);
						LCD_WriteChar(keyValue);
						cell++;
					}
					else if (keyValue == '=')
					{
						//LCD_WriteChar(keyValue);
						LCD_SetCursor(2,6);
						break;
					}
				}
				decimalToHex(num);
			}
			if (keyValue == '3')  // Binary To Decimal
			{
				LCD_Clear();
				LCD_WriteStr((u8*)"Bin 2 Dec");
				_delay_ms(800);
				LCD_Clear();
				LCD_SetCursor(1,1);
				LCD_WriteStr((u8*)"BIN: ");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"DEC: ");
				for (u8 i = 0 ; i < 10; i++)
				{
					binary[i] = 0;
				}
				cell = 0;
				size = 0;
				while(1)
				{
					keyValue = KEYPAD_GetKey();
					if (keyValue == 'Q')
					{
						for (u8 i = 0 ; i < 10; i++)
						{
							binary[i] = 0;
						}
						cell = 0;
						size = 0;
						LCD_Clear();
					}
					else if ((keyValue != NO_KEY) && (keyValue == '0'|| keyValue == '1'))
					{
						binary[size] = keyValue;
						LCD_SetCursor(1,cell+6);
						LCD_WriteChar(keyValue);
						size++;
						cell++;
					}
					else if (keyValue == '=')
					{
						//LCD_WriteChar(keyValue);
						LCD_SetCursor(2,6);
						break;
					}
				}
				LCD_WriteNumber(binaryToDecimal(binary));
			}
			if (keyValue == '4')  // Binary To Hex
			{
				LCD_Clear();
				LCD_WriteStr((u8*)"Bin 2 Hex");
				_delay_ms(800);
				LCD_Clear();
				LCD_SetCursor(1,1);
				LCD_WriteStr((u8*)"BIN: ");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"HEX: ");
				cell = 0;
				size = 0;
				for (s16 i = 0 ; i < 10; i++)
				{
					binary[i] = 0;
				}
				cell = 0;
				size = 0;
				while(1)
				{
					keyValue = KEYPAD_GetKey();
					if (keyValue == 'Q')
					{
						for (u8 i = 0 ; i < 10; i++)
						{
							binary[i] = 0;
						}
						cell = 0;
						size = 0;
					}
					else if ((keyValue != NO_KEY) && (keyValue == '0'|| keyValue == '1'))
					{
						binary[size] = keyValue;
						LCD_SetCursor(1,cell+6);
						LCD_WriteChar(keyValue);
						size++;
						cell++;
					}
					else if (keyValue == '=')
					{
						//LCD_WriteChar(keyValue);
						LCD_SetCursor(2,6);
						break;
					}
				}
				binaryToHex(binary);
			}
			if (keyValue == '5') // Hex to decimal
			{
				LCD_Clear();
				LCD_WriteStr((u8*)"Hex 2 Dec");
				_delay_ms(800);
				LCD_Clear();
				LCD_SetCursor(1,1);
				LCD_WriteStr((u8*)"HEX: ");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"DEC: ");
				//entryFlag = 1;
				cell = 0;
				size = 0;
				while(1)
				{
					keyValue = KEYPAD_GetKey();
					if (keyValue == 'Q')
					{
						cell = 0;
						size = 0;
					}
					else if ((keyValue != NO_KEY) && ((keyValue >= '0'&& keyValue <= '9') || (keyValue >= 'A'&& keyValue <= 'F') ))
					{
						hexNum[size] = keyValue;
						LCD_SetCursor(1,cell+6);
						LCD_WriteChar(keyValue);
						size++;
						cell++;
					}
					else if (keyValue == '=')
					{
						//LCD_WriteChar(keyValue);
						LCD_SetCursor(2,6);
						break;
					}
				}
				LCD_WriteNumber(HexStringToDecimal(hexNum));
			}
		}
	}
}


