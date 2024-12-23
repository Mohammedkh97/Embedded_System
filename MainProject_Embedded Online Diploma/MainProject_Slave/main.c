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

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

//volatile u8 flag;   // To make interrupt difraing

volatile u8 flag;
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

volatile u8 data[20];

void Stack_callback(void)
{	
	static u8 i = 0;
	data[i] = UART_ReceiveData_NO_BLOCK();
	i++;
}


int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	UART_init();
	//EXI_init();
	
	u16 x= 0 , c2 = 0;
	//u32 t1 = 0,t2 = 0 , time = 0;
	EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1 , RISING_EDGE);

	//EXI_Enable(EX_INT0);
	//EXI_Enable(EX_INT1);

	//EXI_SetCallBack(EX_INT0 , f1);
	GLOBAL_ENABLE();

	// Enable OV flow interrupt
	//TCNT0 = 6;
	TCCR0 = 2; //Timer is normal mode at 8 Prescaler lOOK At Data sheet   // clkI/O/8 (From prescaler)

	//SET_BIT(TCCR0 , WGM01);
	//SET_BIT(TCCR0 , COM00);  // When you disable global interrupt, OC PIN Only will display
	/*SET_BIT(TCCR0 , COM01);
	SET_BIT(TCCR0 , COM00);
	SET_BIT(TCCR0 , WGM01);
	SET_BIT(TCCR0 , WGM00);*/
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	//Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	//TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	//TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8);
	//TIMER0_OC0Mode(OC0_NON_INVERTING);

	//t1= TCNT0;
	//ADC_ReadVolt(CH_0);  // 216 us
	//_delay_us(100);
	//DIO_WritePin1(PINC0 , HIGH);
	//_delay_us(300);
	//DIO_WritePin1(PINC0, LOW);
	//while(!GET_BIT(PIND, 0));
	//t2 = TCNT0;
	//c2 = c;
	//time = (t2 - t1) + c*256;
	
	u8 angle = 0;
	OCR1A =999 ; // Zero Position
	SERVO_WriteAngle(0);
	_delay_ms(1000);
	OCR1A =10 ; // Zero Position
	_delay_ms(1000);
	OCR1A =60 ; // Zero Position
	_delay_ms(1000);
	OCR1A =160 ; // Zero Position
	_delay_ms(1000);
	OCR1A =200 ; // Zero Position
	_delay_ms(1000);
	OCR1A =250 ; // Zero Position
	_delay_ms(1000);
	OCR1A =300 ; // Zero Position	

while(1)
{
	
}
	Ultrasonic_init();
	
	u8 distance =  0;
	
	//Ultrasonic_Trigger_t US1 , US2;
	//Timer1_ICU_SetCallBack(InputCaptureFunction);
	//Timer1_InputCaptureEdge(RISING);
	//LCD_SetCursor(1,1);
	//LCD_WriteStr((u8*)"UART");
	u8 i = 0 ;
	u32 num;
	u8 *str[10];
	/*UART_SendData('m');
	UART_SendData('o');
	UART_SendData('h');
	UART_SendData('a');
	UART_SendData('m');
	UART_SendData('e');
	UART_SendData('d');*/
	
	//UART_SendString((u8*)"Mohammed");
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
	
	
	while (1)
	{
		// Code here
		/*x = ADC_Read(CH_0);
		OCR0 = 255 - (x/4);*/
		
		// The number nine and its multiples produce integer numbers
		
		for (angle = 0 ; angle < 180 ; angle++)
		{
		SERVO_WriteAngle(angle);
		_delay_ms(50);

		}
		
		for (angle = 180 ; angle > 0 ; angle--)
		{
		SERVO_WriteAngle(angle);
		_delay_ms(50);
		}
		
		
		/*flag = 0;
		TCNT1 = 0;
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		
		DIO_WritePin1(PINC1,HIGH);
		_delay_us(10);
		DIO_WritePin1(PINC1 , LOW);
		while(flag < 2);
		u16 time = t2 - t1;
		distance = time / 58;
		LCD_SetCursor(1,1);
		LCD_WriteNumber(distance);*/
		

		distance = Ultrasonic_Get_Distance(ULTRASONIC_1);
		LCD_SetCursor(1,1);
		LCD_WriteNumber(distance);
		_delay_ms(60);
		distance = Ultrasonic_Get_Distance(ULTRASONIC_2);
		LCD_SetCursor(1,10);
		LCD_WriteNumber(distance);
		
		//UART_SendStringAsynchronous_NO_BLOCK((u8*)"Mohammed Khalaf");
		//data = UART_ReceiveData();
		/*UART_ReceiveString(str);
		LCD_SetCursor(2,1);
		LCD_WriteStr(str);
		

		i++;
		
		LCD_SetCursor(1,10);
		LCD_WriteNumber(i);
		//UART_SendData(x+'0');
		x++;
		_delay_ms(200);*/
	/*	data[i] = UART_ReceiveData();
		if (data[i]> 0)
		{
			if (pushData(data) == STACK_FULL)
			{
				UART_SendString((u8*)"Stack is Full");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"Stack is Full");
			}
			else
			{
			UART_SendString((u8*)"Data is pushed");
			LCD_SetCursor(2,1);
			LCD_WriteStr((u8*)"Data is pushed");
			}
		}
		else if (DIO_ReadPin1(PINC0) == LOW)
		{
			popData(&data);
			if (popData(&data) == STACK_EMPTY)
			{
				UART_SendString((u8*)"Sack is Empty");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"Sack is Empty");
			}
			else
			{
				UART_SendString((u8*)"Data is popped");
				LCD_SetCursor(2,1);
				LCD_WriteStr((u8*)"Data is popped");				
			}
			
		}*/
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




/*ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
DIO_TogglePin(PIND0);
flag = 1;
LCD_SetCursor(2,5);
LCD_WriteStr((u8*)"INT0");
//_delay_ms(2000);
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


