/*
* MainProject.c
*
* Created: 10/9/2023 1:44:16 AM
* Author : Mohammed Khalaf
*/
#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "ADC_int.h"

#include "SegmentDisplay.h"
#include "MOTOR_Interface.h"
#include "MOVE.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"
#include "Sensors_int.h"
#include "TempFilter.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	DIO_init();
	LCD_Init();	
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	
	while (1)
	{
		/*u16 Temp = SENSORS_LM35_ReadTemp(); // // Note: Here Temp in (C*10)
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Temp: ");
		LCD_SetCursor(2,7);
		
		LCD_WriteNumber(Temp / 10);
		LCD_WriteChar('.');
		LCD_WriteNumber(Temp%10);
		LCD_WriteStr((u8*)" ");*/
		
		/*u16 Pressure = SENSORS_MPX4115_ReadPressure();
		LCD_SetCursor(1,1);
		LCD_WriteStr((u8*)"ADC Read: ");
		LCD_SetCursor(1, 11);
		u16 adc = ADC_Read(CH_7);
		LCD_WriteNumber(adc);
		LCD_WriteStr((u8*)" ");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Press: ");
		//LCD_SetCursor(2,10);
		
		LCD_WriteNumber(Pressure / 10);
		LCD_WriteChar('.');
		LCD_WriteNumber(Pressure%10);
		LCD_WriteStr((u8*)"kPa");
		LCD_WriteStr((u8*)" ");*/
		
		Temp_Runnable();
		
		LCD_SetCursor(1,1);
		LCD_WriteStr((u8*)"Filtered: ");
		LCD_SetCursor(1, 10);
		LCD_WriteNumber(Temp_Get_Filtered() / 10);
		LCD_WriteChar('.');
		LCD_WriteNumber(Temp_Get_Filtered() % 10);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"UnFiltered: ");
		LCD_SetCursor(2, 12);
		LCD_WriteNumber(Temp_Get_Unfiltered() / 10);
		LCD_WriteChar('.');
		LCD_WriteNumber(Temp_Get_Unfiltered() % 10);
		LCD_WriteStr((u8*)"   ");
		
	}
	return 0;
}