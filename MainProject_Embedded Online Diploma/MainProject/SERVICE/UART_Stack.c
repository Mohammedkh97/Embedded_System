/*
 * UART_Stack.c
 *
 * Created: 1/9/2024 9:14:06 PM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "DIO_interface.h"
#include "UART_Stack.h"

static u8 stack[Stack_Size];
static u8 stackPtr;
u8 data;

stack_Status pushData(u8 data)
{
	// To follow MISRA Rules:
	
	stack_Status status = STACK_DONE;
	if (stackPtr == Stack_Size)
	{
		 // return STACK_FULL; // MISRA rules dosen't let you use multi returns
		status = STACK_FULL;
	}
	else
	{
		stack[stackPtr] = data;
		stackPtr++;
		status = STACK_DONE;

	}
	return status;
}
stack_Status popData(u8 *data)
{
	stack_Status status = STACK_DONE;
	if (stackPtr == 0)
	{
		status = STACK_EMPTY;
	//	return STACK_EMPTY;
	}
	else
	{
		stackPtr--;
		*data = stack[stackPtr];
		status = STACK_DONE;
	}
	
	return status;
}

