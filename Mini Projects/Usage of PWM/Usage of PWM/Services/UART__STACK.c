#include "stdTypes.h"
#include "Utils.h"#include "UART_STACK.h"static u8 stack[STACK_SIZE];static u8 sp=0;stack_status_t push(u8 data){	if(sp==STACK_SIZE)	{		return STACK_FULL;	}	else	{		stack[sp]=data;		sp++;		return DONE;	}}stack_status_t pop(u8 * pdata){	if(sp == 0)	{		return STACK_EMPTY;	}	else	{		sp--;		*pdata = stack[sp];		return DONE;	}}

