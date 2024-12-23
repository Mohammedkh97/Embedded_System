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
#include "Ex_int.h"
#include "SERVO_int.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Ultrasoinc.h"
#include "UART.h"
#include "UART_Services.h"
#include "UART_Stack.h"
#include "RGB.h"
#include "RGB_Config.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

volatile u8 flag = 0;
volatile u16 t1 , t2;




volatile u8 data[20] ;

volatile u8 stack[Stack_Size];
static u8 stackPtr = 0;
u8 receivedData = 0;
u8 stackFullFlag = 0;
u8 stackEmptyFlag = 0;

void Stack_callback(void)
{
	static u8 i = 0;
	data[i] = UART_ReceiveData_NO_BLOCK();
	i++;
	flag++;
}
void UART_Stack_callback(void)
{
	//static u8 i = 0;
	stack[stackPtr] = UART_ReceiveData_NO_BLOCK();
	
	if (pushData(stack[stackPtr]) == STACK_DONE)
	{
		if (stackEmptyFlag == 1)
		{
			LCD_WriteStringCursor(2,1,(u8*)"                    ");
			stackEmptyFlag = 0;
			//stackPtr = 0;
		}
		
		LCD_SetCursor(2, stackPtr+1);
		LCD_WriteChar(stack[stackPtr]);
		stackPtr++;
	}
	else if (pushData(stack[stackPtr]) == STACK_FULL)
	{
		LCD_SetCursor(2, 1);
		LCD_WriteStr((u8*)" Stack is Full  ");
		stackFullFlag = 1;
	}

}



int main(void)
{
	DIO_init();
	LCD_Init();
	UART_init();
	EXI_init();
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);

	u8 val=0;

	
	//SERVO_WriteAngle(120);
	
	RGB(0,RED);

	UART_RX_Interrupt_Enable();
	UART_RX_SetCallback(UART_Stack_callback);
	Global_Interrupt_Enable();

	while (1)
	{
		
		//if (DIO_ReadPin1(PIND2) == LOW)
		//{
		//while (!DIO_ReadPin1(PIND2));  //Busy wait for the push button pressing

	
		
		//}
		
		/*
		if (pushData(receivedData) == STACK_DONE)
		{
		stackPtr++;
		//LCD_SetCursor(2, stackPtr);
		//LCD_WriteChar(receivedData);
		}
		else
		{
		if (stackPtr >= Stack_Size || (pushData(receivedData) == STACK_FULL))
		{
		//LCD_SetCursor(2, 1);
		//LCD_WriteStr((u8*)" Stack is Full  ");
		}
		}
		*/
		/*if (DIO_ReadPin1(PINC0) == LOW)
		{
		DIO_WritePin1(PINC3,HIGH);
		_delay_ms(500);
		DIO_WritePin1(PINC3,LOW);
		_delay_ms(500);
		}*/
		//if (flag > 0)
		//{
		
		/*
		LCD_SetCursor(2,i);
		LCD_WriteChar(data[i-1]);
		flag --;
		i++;
		*/
		
		//  once delay is done all data stored in array or its buffer will be sent as a string at a time
		/*LCD_SetCursor(2,1);
		LCD_WriteStr(data);
		flag = 0;
		i++;	*/
		//}
		
		/*LCD_SetCursor(2,10);
		LCD_WriteStr((u8*)"Mohamed");
		UART_ReceiveString_DockLight(str); // Synchronous function
		LCD_SetCursor(2,1);
		LCD_WriteStr(str);*/
		LCD_SetCursor(1,10);
		LCD_WriteNumber(val);
		val++;
		if (val==100)
		{
			val = 0;
		}
		_delay_ms(500);
	}
	return 0;
}


ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	if (popData(&stack[stackPtr]) == STACK_EMPTY)
	{
		LCD_SetCursor(2, 1);
		LCD_WriteStr((u8*)" Stack is Empty  ");
		stackEmptyFlag = 1;
	}
	else
	{
		if (stackEmptyFlag == 1)
		{
			LCD_WriteStringCursor(2,1,(u8*)"                 ");
			stackEmptyFlag = 0;
		}
		if (stackFullFlag == 1)
		{
			LCD_WriteStringCursor(2,1,(u8*)"                    ");
			LCD_WriteStringCursor(2,1,(u8*)stack);
			LCD_SetCursor(2, stackPtr+1);
			LCD_WriteChar(' ');
			stackFullFlag = 0;
		}
		stackPtr--;
		LCD_SetCursor(2, stackPtr+1); // Adjust the cursor position
		LCD_WriteChar(' '); // Clear the character from the LCD
	}
}
