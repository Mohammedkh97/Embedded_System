/*
* KEYPAD_init.c
*
* Created: 10/31/2023 4:49:00 PM
*  Author: Mohammed Khalaf
*/
#define KEYPAD_PROG

#include "stdTypes.h"
#include "DIO_interface.h"

#include "KEYPAD_Config.h"
#include "KEYPAD_int.h"


#define CLOCK  16

#define F_CPU 8000000UL
#include <util/delay.h>

void KEYPAD_init(void)
{	u8 row /*, col*/;
	for (row = 0 ; row < ROW ; row++)
	{
		DIO_WritePin1(FIRST_OUTPUT + row , HIGH);
	}
	
	/*for (col = 0 ; col < COL ; col++)
	{
		DIO_WritePin1(FIRST_INPUT + col , HIGH);
	}*/
	
}

u8 KEYPAD_GetKey(void)
{
	u8 row, col, key = NO_KEY;
	for (row = 0 ; row < ROW ; row++)
	{
		DIO_WritePin1(FIRST_OUTPUT +row , LOW);
		for (col = 0 ; col < COL ; col++)
		{
			if (!DIO_ReadPin1(FIRST_INPUT+col))
			{
				key = KeysArray[row][col];
				_delay_ms(10);
				while (!DIO_ReadPin1(FIRST_INPUT + col));
				_delay_ms(10);
			}
		}
		DIO_WritePin1(FIRST_OUTPUT+row, HIGH);
	}
	return key;
}
