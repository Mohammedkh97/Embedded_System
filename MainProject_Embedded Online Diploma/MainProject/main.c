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
#include "RGB_Application_File.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

//volatile u8 flag;   // To make interrupt difraing


volatile u8 flag = 0;
volatile u16 t1 , t2;

static volatile u8 flag2 ,c;


void f1()
{
	flag2 = 1;
	DIO_TogglePin(PIND0);
}

void f2()
{
	flag2 = 1;
	DIO_TogglePin(PIND1);
}

void InputCaptureFunction()
{
	if (flag == 0)
	{
		t1 = ICR1;
		flag = 1;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		flag = 2;
		Timer1_ICU_InterruptDisable();
		Timer1_InputCaptureEdge(RISING);
	}
	
}
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
			LCD_Goto_WriteString(2,1,(u8*)"                    ");
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
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	UART_init();
	EXI_init();
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	u8 x= 0 , c2 = 0;
	//u32 t1 = 0,t2 = 0 , time = 0;
	
	//EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	//EXI_TriggerEdge(EX_INT1 , RISING_EDGE);

	//EXI_Enable(EX_INT0);
	//EXI_Enable(EX_INT1);

	//EXI_SetCallBack(EX_INT0 , f1);
	
	//Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	//Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	//Timer1_OCRA1Mode(OCRA_INVERTING);  //     OCRA_INVERTING     = CLEAR      // TON  = Value of OCR   Zero will not be calculated
	//Timer1_OCRB1Mode(OCRB_INVERTING);	   // OCRA_NON_INVERTING = SET        // TOFF = Value of OCR
	//TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8);
	//TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	//TIMER0_OC0Mode(OC0_CLEAR);           // OCRA_NON_INVERTING = SET // TOFF = Value of OCR  100 % will not be calculated  255 is the zero value 
	
	//Ultrasonic_init();
	
	u8 distance =  0;
	//Ultrasonic_Trigger_t US1 , US2;
	//Timer1_ICU_SetCallBack(InputCaptureFunction);
	//Timer1_InputCaptureEdge(RISING);
	LCD_SetCursor(1,1);
	LCD_WriteStr((u8*)"UART");
	/*LCD_SetCursor(2,10);
	LCD_WriteStr((u8*)"Mohammed");*/
	u8 i = 1 ;
	u32 num;
	u8 str[20];
	
	//UART_SendString((u8*)"Mohammed");  // Synchronous function
	
	//UART_SendStringAsynchronous((u8*)"Mohammed Khalaf");
	
	/*	endian_t E = Endian_Check();
	if (E == LITTLE)
	{
	UART_SendString((u8*)"LITTLE");
	}
	else
	{
	UART_SendString((u8*)"BIG");
	}*/
	//UART_SendStringAsynchronous_NO_BLOCK((u8*)"Mohammed Khalaf"); // This function must be called in while(1)
	//UART_SendNumber(300);
	
	//UART_SendStringCheckSum((u8*)"Mohammed");
	//UART_RX_Interrupt_Enable();
	//UART_RX_SetCallback(Stack_callback);
	
	u8 val=0;

	
	//SERVO_WriteAngle(120);
	u8 shape[] ={
		0x10,
		0x08,
		0x06,
		0x08,
		0x10,
		0x00,
		0x00,
		0x00
	};
	

	/*UART_RX_Interrupt_Enable();
	UART_RX_SetCallback(UART_Stack_callback);
	Global_Interrupt_Enable();*/
	/*ICR1 = 255;
	OCR0 = 0;
	OCR1A = 0;
	OCR1B = 250;*/
	RGB_App_init();
	//RGB(RGB_NUM,BLUE);
	//RGB_Set_PWM(RGB_NUM , RED_PIN_DUTY_CYCLE , GREEN_PIN_DUTY_CYCLE , BLUE_PIN_DUTY_CYCLE);
	RGB_Select();
	RGB_Color_Selection();
	while (1)
	{
		RGB_Color_Selection();
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
		//LCD_SetCursor(1,10);
		//LCD_WriteNumber(val);
		//val++;
		if (val==100)
		{
			val = 0;
		}
		//_delay_ms(500);
		/*OCR0 = x+1;
		OCR1A = 50+x;
		OCR1B = 100+x;
		x++;*/
	//RGB(0,BLUE);
		
		
	}
	return 0;
}


/*ISR(TIMER0_OVF_vect)
{
DIO_TogglePin(PIND0);
TCNT0 = 156; // Start counting from 156 to make sure that the timer will count 100 counts and overflow
}
*/


/*
ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
static u16 c2 = 0;
c++;
c2++;
// Here counter TCNT starts from zero .This means interrupts comes every 256 counts
if (c == 3906)
{
TCNT0 = 192;
DIO_TogglePin(PIND0);
c = 0;

}

if (c2 == 1953)
{
DIO_TogglePin(PIND1);
c2 = 0;
}


}
*/

/*
// With one counter
ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile	static u16 c2 = 0;
c++;
// Here counter TCNT starts from zero .This means interrupts comes every 256 counts
// 1000000 / 256 = 1906.25
// To calculate 0.25 within the total time:
// No of interrupts = 3907
if (c == 3907)
{
TCNT0 = 192;
DIO_TogglePin(PIND0);
DIO_WritePin1(PIND1 , LOW);
c = 0;

}
if (c == 1953)
{
DIO_TogglePin(PIND1);

}
}
*/

/*
ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile	static u16 c2 = 0;
c++;
//  To calculate 0.25 within the total time:
//  TCNT starts from 6 .This means interrupts comes every 250 counts
//  To calculate 0.25 within the total time:
//  1000000 / 250 = 4000

TCNT0 = 6;

if (c == 4000)
{
TCNT0 = 192;
DIO_TogglePin(PIND0);
DIO_WritePin1(PIND1 , LOW);
c = 0;

}
if (c == 2000)
{
DIO_TogglePin(PIND1);

}
}*/


/*
ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile	static u16 c2 = 0;
TCNT0 = 6;
c++;

if (c == 10)
{

DIO_WritePin1(PIND0 , HIGH);

}
else if (c == 30)
{
DIO_WritePin1(PIND0 , LOW);
c = 0;
}
}

*/

// Task 1:

/*ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
static u16 c2 = 0;
static u16 c3 = 0;
TCNT0 = 6;
c++;
c2++;
c3++;

if (c == 20)
{
DIO_TogglePin(PIND0);
c = 0;

}

if (c2 == 40)
{
DIO_TogglePin(PIND1);
c2 = 0;
}

if (c3 == 100)
{
DIO_TogglePin(PIND4);
c3 = 0;
}


}


*/
/*ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
TCNT0 = 6;
c++;

if (c % 20==0)
{
DIO_TogglePin(PIND0);
}

if (c % 40 == 0)
{
DIO_TogglePin(PIND1);
}

if (c % 100 == 0)
{
DIO_TogglePin(PIND4);
}

if (c== 200)
{
c=0;
}

}
*/

//Task 2:
/* ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
TCNT0 = 6;
c++;
// c%1
DIO_TogglePin(PIND0);

if (c % 2 == 0)
{
DIO_TogglePin(PIND1);
}

if (c % 5 == 0)
{
DIO_TogglePin(PIND4);
}

if (c== 10)
{
c=0;
}

}
*/

// Task 3:
/*ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
static u16 c = 0; // static local is better because we don't need this variable in main. If it is global, it must be volatile
TCNT0 = 255;

DIO_TogglePin(PIND0);

}

*/


/*
ISR(TIMER0_OVF_vect)
{	// Calculate number of interrupts and every interrupt occurs means ISR executed, so that counter of interrupt must be static local or global
// static local is better because we don't need this variable in main. If it is global, it must be volatile
//static u8 c;
//TCNT0 = 255;
//OCR0 = 100;
c++;
DIO_TogglePin(PIND0);
}



ISR(TIMER0_OC_vect)
{
static int angle = 0;
//OCR0 = 100;
DIO_TogglePin(PIND1);
SERVO_WriteAngle(angle);
angle+=9;
OCR0 = OCR0 + 9;
}

*/


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
			LCD_Goto_WriteCharacter(2,1,(u8*)"                 ");
			stackEmptyFlag = 0;
		}
		if (stackFullFlag == 1)
		{
			LCD_Goto_WriteString(2,1,(u8*)"                    ");
			LCD_Goto_WriteString(2,1,(u8*)stack);
			LCD_SetCursor(2, stackPtr+1);
			LCD_WriteChar(' ');
			stackFullFlag = 0;
		}
		stackPtr--;
		LCD_SetCursor(2, stackPtr+1); // Adjust the cursor position
		LCD_WriteChar(' '); // Clear the character from the LCD
	}
}

/*ISR(INT0_vect) {
if (popData(&poppedData) == STACK_DONE)
{
if (stackPtr > 0)
{
stackPtr--;
LCD_SetCursor(2, stackPtr+1);
LCD_WriteChar(' '); // Clear the character from the LCD
}
}
else
{
LCD_SetCursor(2, 1);
LCD_WriteStr((u8*)" Stack is Empty");
}
}
*/
/*ISR(INT1_vect)				 // Works on Rising Edge
{

DIO_TogglePin(PIND1);
LCD_SetCursor(2,5);
LCD_WriteStr((u8*)"INT1");
//_delay_ms(1000);
}*/

// The execution of interrupts depends on the Rank of them in Vector Table

// If you did interrupt without ISR main function will be reset once you make an interrupt


