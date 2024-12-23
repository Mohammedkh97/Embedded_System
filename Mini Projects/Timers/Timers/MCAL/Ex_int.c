/*
* EX_int.c
*
* Created: 11/19/2023 10:28:08 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "Ex_int.h"

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=Null_Ptr;
static void (*INT1_Fptr) (void)=Null_Ptr;
static void (*INT2_Fptr) (void)=Null_Ptr;

/************************************Enable/Disable functions***********************************/

void EXI_init(void)
{
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
}


void EXI_Enable(ExInterruptSource_t Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
}

void EXI_Disable(ExInterruptSource_t Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		CLEAR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLEAR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLEAR_BIT(GICR,INT2);
		break;
	}
}

void EXI_Init(void)
{
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
}


/************************************Control function*****************************/

void EXI_TriggerEdge(ExInterruptSource_t Interrupt,TriggerEdge_t Edge)
{
	switch(Interrupt){
		case EX_INT0:
		switch(Edge){
			case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
		}
		break;
		case EX_INT1:
		switch(Edge){
			case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
		}
		break;
		case EX_INT2:  // INT2 is Asynchronous External Interrupt (Don't care for CPU Clock. Don't Support ANY_LOGIC_CHANGE or LOW_LEVEL.
		switch(Edge){
			case FALLING_EDGE:
			CLEAR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			default:
			CLEAR_BIT(MCUCSR,ISC2);
		}
		break;
	}
}

/************************************Call back functions*********************************************/

void EXI_SetCallBack(ExInterruptSource_t Interrupt, void(*LocalPtr)(void))
{
	switch(Interrupt){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;
		
	}
}


/*******************************ISR********************************/

//ISR(INT0_vect)
//{
	/*code validate data*/
	/* data right address*/
	//u8 data=5;
	//EXI0_Func(data);  // Call out function  
	// 
	
/*	if (INT0_Fptr!=Null_Ptr)   // Without checking if the pointer to function is equal zero the compiler will reset the code
	{
		INT0_Fptr();
	}*/
	
	
//}
/*ISR(INT1_vect,ISR_NOBLOCK)
{

	if (INT1_Fptr!=Null_Ptr)
	{
		INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if (INT2_Fptr!=Null_Ptr)
	{
		INT2_Fptr();
	}
	
}*/