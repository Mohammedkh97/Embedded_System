/*
* LCD_init.c
*
* Created: 10/24/2023 12:44:29 PM
*  Author: Mohammed Khalaf
*/
#include "stdTypes.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "LCD_Config.h"
#include "LCD_Private.h"
#include "Utils.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

#if LCD_MODE == _4_BIT

void write_instruction(u8 instruction)
{

	DIO_WritePin1(RS , LOW);
	DIO_WritePin1(D7 , GET_BIT(instruction , 7));
	DIO_WritePin1(D6 , GET_BIT(instruction , 6));
	DIO_WritePin1(D5 , GET_BIT(instruction , 5));
	DIO_WritePin1(D4 , GET_BIT(instruction , 4));
	
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
	
	DIO_WritePin1(D7 , GET_BIT(instruction , 3));
	DIO_WritePin1(D6 , GET_BIT(instruction , 2));
	DIO_WritePin1(D5 , GET_BIT(instruction , 1));
	DIO_WritePin1(D4 , GET_BIT(instruction , 0));
	
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
	
}

void write_Data(u8 Data)
{
	DIO_WritePin1(RS , HIGH);
	DIO_WritePin1(D7 , GET_BIT(Data , 7));
	DIO_WritePin1(D6 , GET_BIT(Data , 6));
	DIO_WritePin1(D5 , GET_BIT(Data , 5));
	DIO_WritePin1(D4 , GET_BIT(Data , 4));
	
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
	
	DIO_WritePin1(D7 , GET_BIT(Data , 3));
	DIO_WritePin1(D6 , GET_BIT(Data , 2));
	DIO_WritePin1(D5 , GET_BIT(Data , 1));
	DIO_WritePin1(D4 , GET_BIT(Data , 0));
	
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50); // to make sure that Micro-controller starts first
	write_instruction(0x02);
	write_instruction(0x28);
	write_instruction(0x0c);  // 0x0E     0x0F     Cursor
	write_instruction(0x01);  // Clear LCD
	_delay_ms(1);
	write_instruction(0x06);
	
}

#elif LCD_MODE == _8_BIT

void write_instruction(u8 instruction)
{

	DIO_WritePin1(RS , LOW);
	DIO_Write_Port(LCD_PORT , instruction);
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
	
}
void write_Data(u8 data)
{
	DIO_WritePin1(RS , HIGH);
	DIO_Write_Port(LCD_PORT , data);
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	_delay_ms(50); // to make sure that Micro-controller starts first
	/*                       */
	/* DIO_WritePin1(RS , LOW);
	DIO_Write_Port(LCD_PORT , 0x38); // 0x38 from data sheet page 18 function set 0 0 0 1 1 1 0 0 0  (Back to Data sheet)
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);*/
	write_instruction(0x38);
	write_instruction(0x0c);  // 0x0E     0x0F     Cursor
	write_instruction(0x01);  // Clear LCD
	_delay_ms(1);
	write_instruction(0x06);
}

#endif


/*******************************************************************************/



/*
-Data ON PORTA = 01101101;
-New Data you want to write on PORTA: 11001110
You want to write Data on the second half of PORTA
1. Get the second four bits:
Data & 0xF0 :	11001110
11110000
= 	11000000
2. Clear the Data of PORTA for the the second four bits only
PA = PA & 0x0F: 01101101
00001111
=	00001101
3. Set the New you want to write on PORTA
PA = PA | data & 0xF0:
00001110
| ( 11001110
&   11110000)  // For the second data four bits:
PA = PA | data<<4 & 0xF0:
00001110
| ( 11001110
&   11110000)  // For the first data four bits:				PA = PA | data & 0xF0:


*/



void LCD_WriteChar(u8 ch)
{
	write_Data(ch);
}
void LCD_WriteStr(u8* str)
{
	u8 i;
	for (i = 0 ; str[i] ; i++)
	{
		write_Data(str[i]);
	}
	str[i] = 0;
	
}

void LCD_WriteNumber(s32 num)
{
	u8 str[10];
	intoString(num , str);
	LCD_WriteStr(str);
	
}

void LCD_Clear(void)
{
	write_instruction(0x01);  // Clear LCD
	_delay_ms(1);
	// Keep in mind, clear command sets DDRAM address to 00H "From the begin"
}

void LCD_SetCursor(u8 line , u8 cell)
{
	/*
	line: 1 - 2
	cell: 1 - 16
	*/
	if (line == 1)
	{
		write_instruction(0x80 + (cell - 1));  // Have a look in the LCD Data sheet: 0b10000000 = 0x80
		_delay_us(40);
	}
	else if (line == 2)
	{
		write_instruction(0x40 + 0x80 + (cell - 1));
		_delay_us(40);
	}
	else if (line == 3)
	{
		write_instruction(0x94 + (cell - 1));
		_delay_us(40);
	}
	else if (line == 4)
	{
		write_instruction(0xd4 + (cell - 1));
		_delay_us(40);
	}	
	
	
}

void LCD_Binary_Number_Display(s32 num)
{
	/*s32 i;
	for (i = 7 ; i>= 0; i--)
	{
	LCD_WriteChar(GET_BIT(num , i) + '0');
	
	}*/
	Dec_Bin(num);
}

void LCD_Hex_Number_Display(s32 num)
{ 
	// 0001 0001 = 1 1 == 17
	
	s8 firstDigit = num%16;
	s8 secondDigit = num/16;
	if (secondDigit<10)
	{
		LCD_WriteChar(secondDigit +'0');
	}
	else
	{
		LCD_WriteChar(secondDigit+'A'-10);
	}
	if (firstDigit<10)
	{
		LCD_WriteChar(firstDigit +'0');
	}
	else
	{
		LCD_WriteChar(firstDigit+'A'-10);
	}
	
}
void LCD_ASCII_Number_Display(u8 ascii)
{
	LCD_WriteNumber(ascii);
}

void LCD_Goto_WriteNumber(u8 line,u8 cell,u32 num)
{
	LCD_SetCursor(line , cell);
	LCD_WriteNumber(num);
}
void LCD_Goto_WriteCharacter(u8 line,u8 cell,u8 character)
{
	LCD_SetCursor(line , cell);
	LCD_WriteChar(character);
}
void LCD_Goto_WriteString(u8 line, u8 cell, u8* str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteStr(str);
	
}