/*
 * UART_Stack.h
 *
 * Created: 1/9/2024 9:12:33 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UART_STACK_H_
#define UART_STACK_H_

#define Stack_Size   20


typedef enum
{
	STACK_FULL,
	STACK_EMPTY,
	STACK_DONE
	
}stack_Status;

stack_Status pushData(u8 data);
stack_Status popData(u8 *data);




#endif /* UART_STACK_H_ */