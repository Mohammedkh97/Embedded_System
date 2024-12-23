#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "Timers.h"

#define F_CPU 8000000UL
#include <util/delay.h>

/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*Timer1_OVF_Fptr) (void)=NullPtr;
static void (*Timer1_OCA_Fptr) (void)=NullPtr;
static void (*Timer1_OCB_Fptr) (void)=NullPtr;
static void (*Timer1_ICU_Fptr) (void)=NullPtr;
/******************************************************************************************/
/*timer 0 functions*/
void TIMER0_Init(Timer0Mode_t mode,Timer0Scaler_t scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
}

void TIMER0_OC0_non_PWM_Mode(OC0_non_PWM_Mode_t OC0_non_PWM_Mode)
{
	switch (OC0_non_PWM_Mode)
	{
		case OC0_DISCONNECTED:
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		case OC0_CLEAR:
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_SET:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_OC0_PWM_Mode(OC0_PWM_Mode_t OC0_PWM_Mode)
{
	switch(OC0_PWM_Mode)
	{
		case OC0_PWM_DISCONNECTED:
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		case OC0_PWM_RESERVED:
		break;
		case OC0_PWM_CLEAR:
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_PWM_SET:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_OC0_Phase_Correct_Mode(OC0_Phase_Correct_Mode_t OC0_Phase_Correct_Mode)
{
	switch(OC0_Phase_Correct_Mode)
	{
		case OC0_Phase_Correct_DISCONNECTED:
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		break;
		
		case OC0_Phase_Correct_RESERVED:
		break;
		
		case OC0_Phase_Correct_CLEAR:
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
		case OC0_Phase_Correct_SET:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_Set_OCR0_Value(u8 Value)
{
	OCR0 = Value;
}


void TIMER0_SetDesiredTime_ms (u32 time_ms)
{
	u32 Ticks = (F_CPU / (TIMER0_SCALER_8 * 1000)) * time_ms;
	
	// Calculate the initial value for TCNT0 register
	u8 initial_TCNT0 = 256 - (u8)(Ticks % 256);
	// Set CTC mode (WGM01 = 2)
	TCCR0 |= (1 << WGM01);

	// Set Prescaler to 8 and start the timer
	SET_BIT(TCCR0 , CS01);
	CLEAR_BIT(TCCR0 , CS00);
	CLEAR_BIT(TCCR0 , CS00);

	// Set the compare value
	OCR0 = (u8)(Ticks / 256);
	// Set initial value for TCNT0 register
	TCNT0 = initial_TCNT0;
	// Enable Timer 0 Compare Match A interrupt
	TIMSK |= (1 << OCIE0);

	// Enable global interrupts
	sei();
}


void TIMER0_SetDesiredTime_us (u32 time_us)
{
	u32 Ticks = (F_CPU / (TIMER0_SCALER_8 * 1000000)) * time_us;
	
	// Calculate the initial value for TCNT0 register
	u8 initial_TCNT0 = 256 - (u8)(Ticks % 256);
	// Set CTC mode (WGM01 = 2)
	TCCR0 |= (1 << WGM01);

	// Set Prescaler to 8 and start the timer
	SET_BIT(TCCR0 , CS01);
	CLEAR_BIT(TCCR0 , CS00);
	CLEAR_BIT(TCCR0 , CS00);

	// Set the compare value
	OCR0 = (u8)(Ticks / 256);
	// Set initial value for TCNT0 register
	TCNT0 = initial_TCNT0;
	// Enable Timer 0 Compare Match A interrupt
	TIMSK |= (1 << OCIE0);

	// Enable global interrupts
	sei();
}

void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE0);
}

/*************************************************************************/
/*timer 1 functions*/
void Timer1_Init( Timer1Mode_t mode,Timer1Scaler_t scaler)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_t oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_CLEAR:
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_SET:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_t oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_CLEAR:
		CLEAR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_SET:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_InputCaptureEdge(ICU_Edge_t edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLEAR_BIT(TCCR1B,ICES1);
}


/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NullPtr)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NullPtr)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NullPtr)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NullPtr)
	{
		Timer1_ICU_Fptr();
	}
}