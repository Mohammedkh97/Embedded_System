/*
* MainProject.c
*
* Created: 10/9/2023 1:44:16 AM
* Author : Mohammed Khalaf
*/
#include "StdTypes.h"
#include "MemMap.h"
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

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

volatile u8 flag;   // To make interrupt difraing


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

int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	ADC_init(VREF_VCC , ADC_SCALER_64);
	//EXI_init();
	
	u16 x= 0 , c2 = 0;
	u32 t1 = 0,t2 = 0 , time = 0;
	
	

	EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1 , RISING_EDGE);

	//EXI_Enable(EX_INT0);
	//EXI_Enable(EX_INT1);

	//EXI_SetCallBack(EX_INT0 , f1);
	//GLOBAL_ENABLE();

	// Enable OV flow interrupt
	//TCNT0 = 6;
	TCCR0 = 2; //Timer is normal mode at 8 Prescaler lOOK At Data sheet   // clkI/O/8 (From prescaler)

	//SET_BIT(TCCR0 , WGM01);
	//SET_BIT(TCCR0 , COM00);  // When you disable global interrupt, OC PIN Only will display
	SET_BIT(TCCR0 , COM01);
	SET_BIT(TCCR0 , COM00);
	SET_BIT(TCCR0 , WGM01);
	SET_BIT(TCCR0 , WGM00);
	
	//DDRB = 0;     // Set PORTD as input
	//PORTB = 0xFF; // Enable pull-up resistors on PORTD
	
	//TIMSK =1; //Enable Interrupt overflow and OC
	
	//SET_BIT(TIMSK , 0);
	//SET_BIT(TIMSK , OCIE0);
	//PORTC =0XFF;
	OCR0 = 100; // Once Timer reach 100 it will send an Interrupt
	TCNT0 = 0;
	c = 0;
	t1= TCNT0;
	//ADC_ReadVolt(CH_0);  // 216 us
	//_delay_us(100);
	//DIO_WritePin1(PINC0 , HIGH);
	//_delay_ms(1);
	//DIO_WritePin1(PINC0, LOW);
	while(!GET_BIT(PIND, 0));
	t2 = TCNT0;
	c2 = c;
	time = (t2 - t1) + c*256;
	
	LCD_SetCursor(2,1);
	LCD_WriteNumber(time);
	LCD_SetCursor(2,10);
	LCD_WriteNumber(c2);
	LCD_SetCursor(1,1);
	LCD_WriteStr((u8*)"TIMER Test  ");

	while (1)
	{
		// Code here
		x = ADC_Read(CH_0);
		OCR0 = 255 - (x/4);
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
	//OCR0 = 100;
	DIO_TogglePin(PIND1);
	//OCR0 = OCR0 + 9; 
	
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
