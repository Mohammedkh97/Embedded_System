
#include "stdTypes.h"
#include "MemoryMap.h"
#include "UART.h"
#include "Utils.h"
#include "UART_Services.h"
#include "UART_Config.h"



static u8 *TX_Str;
static u8 *RX_Str;
static u8 flag=1;

//static u8 i=0;

void Tx_Function_Asynchronous(void)
{
	static u8 i=1;
	
	if (TX_Str[i] != 0)
	{
		UART_SendData_NO_BLOCK(TX_Str[i]);
		i++;
	}
	else
	{
		UART_TX_Interrupt_Disable();
		i = 1;
	}
}

void UART_SendStringAsynchronous(u8*str)
{
	static u8 i=0;
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
	UART_SendData_NO_BLOCK(str[0]);
	TX_Str=str;
	
}


void UART_SendStringAsynchronous_NO_BLOCK(u8* str) // It considered Asynchronous Function due to not complete the task immediately once you pass the string
{
	static u8 i = 0;
	if (flag == 1)
	{
		if (str[i] !=0)
		{
			UART_SendData_NO_BLOCK(str[i]);
			i++;
		}
		flag = 0;
	}
	
}

void UART_Basic_Communication_Module_Init(void)
{
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
}

void UART_Basic_Communication_Module_SendString(u8* str)
{
	TX_Str = str;
}

void UART_Basic_Communication_Module_Runnable(void)
{
	static u8 i = 0;
	if (flag == 1)
	{
		if (TX_Str[i] !=0)
		{
			UART_SendData_NO_BLOCK(TX_Str[i]);
			i++;
		}
		flag = 0;
	}
}

void Rx_Function_Asynchronous()
{
	static u8 i = 0;
	
	RX_Str[i] = UART_ReceiveData_NO_BLOCK();
	i++;
	if (i>20)
	{
		i = 0;
	}
	
}
