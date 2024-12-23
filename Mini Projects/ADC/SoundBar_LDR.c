/*
* ADC.c
*
* Created: 11/7/2023 2:27:17 AM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "LCD_Private.h"
#include "ADC_int.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#LED1      PINC0
#LED2      PINC1
#LED3      PINC2
#LED4      PINC3
#LED5      PINC4
#LED6      PINC5
#LED7      PINC6
#LED8      PINC7

u8 SoundBar[] = {
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};
int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	
	//LCD_WriteStr((u8*)"Mohammed Khalaf  ");
	// When using ADC, Make sure the DIO pins are INFREE
	ADC_init(VREF_VCC , ADC_SCALER_64);
	
	u16 AnalogValue, percentage = 0 , volt = 0;
	/*LCD_SetCursor(2,1);
	LCD_WriteNumber(AnalogValue);*/
	/* Replace with your application code */
	DIO_WritePin1(PINC0 , HIGH);
	_delay_ms(5000);

	while (1)
	{
		
		
		//Sound Bar:
		
		AnalogValue = ADC_Read(CH_0);
		potValue = (AnalogValue*(u32)100)/1023;
		customChar(SoundBar , 1);
		if (AnalogValue > 10)
		{
		LCD_SetCursor(1,1);
		LCD_WriteChar(1);
		}
		if (AnalogValue > 63)
		{
		u8 BarStart = AnalogValue / 63;
		for (u8 i = 1 ; i < BarStart ; i++)
		{
		LCD_SetCursor(1,i);
		LCD_WriteChar(1);
		}
		}
		else if (AnalogValue == 0)
		{
		LCD_SetCursor(1,1);
		LCD_WriteStr((u8*)"   ");
		}
		LCD_SetCursor(1,(AnalogValue/ 63));
		LCD_WriteChar(1);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Analog: ");
		LCD_WriteNumber(AnalogValue);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,14);
		LCD_WriteNumber(potValue);
		LCD_WriteChar('%');
		LCD_WriteStr((u8*)"   ");
		
		
		// Control LEDs using LDR:
		
		AnalogValue = ADC_Read(CH_7);
		percentage = (AnalogValue*(u32)100)/1023;
		LCD_SetCursor(1,1);
		LCD_WriteStr((u8*)"Analog: ");
		LCD_WriteNumber(AnalogValue);
		LCD_WriteStr((u8*)"   ");
		volt = ADC_ReadVolt(CH_7);
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Volt = ");
		LCD_SetCursor(2,8);
		LCD_WriteNumber(volt);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,14);
		LCD_WriteNumber(percentage);
		LCD_WriteChar('%');
		LCD_WriteStr((u8*)"   ");
		if (volt >= 4950)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , HIGH);
			DIO_WritePin1(LED5 , HIGH);
			DIO_WritePin1(LED6 , HIGH);
			DIO_WritePin1(LED7 , HIGH);
			DIO_WritePin1(LED8 , HIGH);
		}
		else if (volt >= 4545 && volt <= 4960)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , HIGH);
			DIO_WritePin1(LED5 , HIGH);
			DIO_WritePin1(LED6 , HIGH);
			DIO_WritePin1(LED7 , HIGH);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 4165 && volt <= 4545)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , HIGH);
			DIO_WritePin1(LED5 , HIGH);
			DIO_WritePin1(LED6 , HIGH);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 3330 && volt <= 4165)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , HIGH);
			DIO_WritePin1(LED5 , HIGH);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 2500 && volt <= 3330)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , HIGH);
			DIO_WritePin1(LED5 , LOW);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 1665 && volt <= 2500)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , HIGH);
			DIO_WritePin1(LED4 , LOW);
			DIO_WritePin1(LED5 , LOW);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 834 && volt <= 1665)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , HIGH);
			DIO_WritePin1(LED3 , LOW);
			DIO_WritePin1(LED4 , LOW);
			DIO_WritePin1(LED5 , LOW);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else if (volt >= 454 && volt <= 834)
		{
			DIO_WritePin1(LED1 , HIGH);
			DIO_WritePin1(LED2 , LOW);
			DIO_WritePin1(LED3 , LOW);
			DIO_WritePin1(LED4 , LOW);
			DIO_WritePin1(LED5 , LOW);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		else
		{
			DIO_WritePin1(LED1 , LOW);
			DIO_WritePin1(LED2 , LOW);
			DIO_WritePin1(LED3 , LOW);
			DIO_WritePin1(LED4 , LOW);
			DIO_WritePin1(LED5 , LOW);
			DIO_WritePin1(LED6 , LOW);
			DIO_WritePin1(LED7 , LOW);
			DIO_WritePin1(LED8 , LOW);
		}
		
	}
}

