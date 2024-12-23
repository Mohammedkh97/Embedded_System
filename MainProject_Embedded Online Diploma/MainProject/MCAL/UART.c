/*
* UART.c
*
* Created: 12/21/2023 2:21:17 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "UART.h"
#include "Utils.h"
#include "UART_Config.h"

static void (*UART_RX_Fptr)(void) = Null_Ptr;
static void (*UART_TX_Fptr)(void) = Null_Ptr;

void UART_init(void)
{
	/* baud rate  9600 with clock 8MHz*/
	UBRRL = 51;
	/*frame size*/
	// 8 bit data 1 Stop bit No parity bit
	// Frame by default value of Registers is set to 8-bit
	/* Enable UART Transmitting and Receiving */
	// Normal Speed
	CLEAR_BIT(UCSRA , U2X);
	
	SET_BIT(UCSRB , TXEN);
	SET_BIT(UCSRB , RXEN);
}

void UART_SendData(u8 data)
{
	while(!GET_BIT(UCSRA , UDRE));  // While data are sent, UDRE = 0, No data means UDRE = 1
	// Sending in progress while UDRE = 0
	UDR = data;
}
u8 UART_ReceiveData()
{
	while(!GET_BIT(UCSRA , RXC)); // Busy wait
	return UDR;
}

u8 UART_ReceiveData_Periodic(u8 *data)  // The advantage of this design is that doesn't delay the rest of code
{
	if (GET_BIT(UCSRA ,RXC))
	{
		*data = UDR;
		return 1;
	}
	return 0;
}

void UART_SendData_NO_BLOCK(u8 data)
{
	UDR = data;
}
u8 UART_ReceiveData_NO_BLOCK()
{

	return UDR;
} 

void UART_RX_Interrupt_Enable(void)
{
	SET_BIT(UCSRB , RXCIE);	
}

void UART_RX_Interrupt_Disable(void)
{
	CLEAR_BIT(UCSRB , RXCIE);
}

void UART_TX_Interrupt_Enable(void)
{
	SET_BIT(UCSRB , TXCIE);
}
void UART_TX_Interrupt_Disable(void)
{
	CLEAR_BIT(UCSRB , TXCIE);
}

void UART_RX_SetCallback(void(*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallback(void(*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

ISR(UART_RX_vect)
{
	if (UART_RX_Fptr != Null_Ptr)
	{
		UART_RX_Fptr();
	}
}
ISR(UART_TX_vect)
{
	if (UART_TX_Fptr != Null_Ptr)
	{
		UART_TX_Fptr();
	}
}

/*
u16 UART_SendFrame_SW(u8 data)
{
	u16 Frame=0;
	u8 Parityflag = 0;
	Frame = data << 1; // Start bit
	// Parity Check Bit:
	if (countSetBits(data) == EVEN && (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1))  // the Second part can be deleted as you can set config file .h and .c
	{
		// Frame = 00000101 0
		Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else if (countSetBits(data) == ODD && (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)) // the Second part can be deleted as you can set config file .h and .c
	{
		Frame = Frame | (ODD << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else
	{
		Parityflag = 0;
		Frame = Frame;
	}
	// Stop Bit:
	if (Stop_Bits == 2 && (GET_BIT(UCSRC , USBS)))
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (3 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (3 << (0 + Data_Length + Start_Bit)) ;
		}
		
	}
	else if (Stop_Bits == 1 && (!GET_BIT(UCSRC , USBS)))  // the Second part can be deleted as you can set config file .h and .c
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (1 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (1 << (0 + Data_Length + Start_Bit)) ;
		}
	}
	return Frame;
}


// Function to count the number of set bits  (ONES)
u8 countSetBits(u16 num)
{
	u8 count = 0;
	while (num) {
		count += num & 1;  // Add the last bit to the count if it is 1
		num >>= 1;         // Right shift the number to remove the processed bit
	}
	
	if (count % 2 == 0)
	{
		return EvenParity;
	}
	else
	return OddParity;
}

Parity_t UART_CheckParity(u8 data)
{
	if (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)
	{
		return ODD;
	}
	else if (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1)
	{
		return EVEN;
	}
}
*/