/*
* Usage of PWM.c
*
* Created: 3/26/2024 12:52:09 PM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "ADC_int.h"

#include "SegmentDisplay.h"
#include "MOTOR_Interface.h"

#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"
#include "Sensors_int.h"
#include "Ex_int.h"
#include "SERVO_int.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Ultrasoinc.h"
#include "UART.h"
#include "UART_Services.h"
#include "UART_Stack.h"
#include "MOTOR_Interface.h"
#include "ConfigFile.h"

#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE , TIMER0_SCALER_8);
	TIMER0_OC0_PWM_Mode(OC0_PWM_CLEAR);
	
	// CLEAR MODE means OCR Value is the TON
	
	/*
	TIMER0_OC0_PWM_Mode(OC0_PWM_SET);
	SET MODE means OCR Value is the TOFF
	OCR0 = 125;
	*/
	
	u16 speedValue = 0 ,temp;
	while (1)
	{
		/*nalog_Value = ADC_Read(CH_0);
		LCD_SetCursor(1,1);
		LCD_WriteStr((u8*)"ADC Value = ");
		LCD_SetCursor(1,12);
		LCD_WriteNumber(analog_Value);
		OCR0 = analog_Value / 4;
		if (analog_Value >= 512)
		{
		Motor_CW(M1);
		}
		else if (analog_Value < 512)
		{
		Motor_CCW(M1);
		}
		
		*/
		
	temp = LM35_Get_Temp();
	
	LCD_Goto_WriteString(2,1,(u8*)"Temp =");
	LCD_Goto_WriteNumber(2,7,temp);
	if (temp > 30)
	{
		// Fan Rotates in Max Speed
		speedValue = ((u16)FASTPWM_MODE * ((u16)(Speed_100 / MAX_SPEED)));
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);

		DIO_WritePin1(PINC0,HIGH);
	}
	
	else if ( temp > 25 && temp <=30)
	{
		// Fan Rotates in Upper Medium Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_60) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	
	else if (temp > 22 && temp <= 25)
	{
		//Fan Rotates in Medium Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_50) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	else if (temp > 20 && temp <= 22)
	{
		//Fan Rotates in Slow Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_15) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	else if (temp <= 20)
	{
		speedValue = (((u16)FASTPWM_MODE * Speed_Stop) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_STOP(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
		
		/*int i = 0;
		for(i = 0; i < 255 ; i++)
		{
		OCR0 = i;
		_delay_ms(10);
		LCD_Goto_WriteString(1,1,"Duty Cycle =");
		LCD_Goto_WriteNumber(1,13, i);
		}
		_delay_ms(500);
		for(i = 255; i > 0 ;  i--)
		{
		OCR0 = i;
		_delay_ms(10);
		LCD_Goto_WriteString(1,1,"Duty Cycle =");
		LCD_Goto_WriteNumber(1,13, i);
		}*/
		
	}
}

