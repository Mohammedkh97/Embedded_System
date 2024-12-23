/*
 * UART_Config.h
 *
 * Created: 12/22/2023 3:14:15 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

void configureUART();

#define EvenParity 0
#define OddParity  1

//#define No_Parity NULL

#define Parity_Type EvenParity

// Even Parity:
/*#define UPM0 0
#define UPM1 1*/

//Odd Parity:
/*#define UPM0 1
#define UPM1 1*/




// Stop Bits Mode
#define ONE   1
#define TWO   2

#define Stop_Bits TWO

#define Start_Bit 1    // Must be found by default
#define Data_Length 8


#endif /* UART_CONFIG_H_ */




/*
#if Parity_Type == EvenParity

CLEAR_BIT(UCSRC , UPM0);
SET_BIT  (UCSRC , UPM1);

u16 UART_SendFrame_SW(u8 data)
{
	u16 Frame=0;
	u8 StopBits = 0 , Parityflag = 0;
	Frame = data << 1; // Start bit
	// Parity Check Bit:
	if (countSetBits(data) == EVEN && (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1))
	{
		// Frame = 00000101 0
		Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else if (countSetBits(data) == ODD && (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1))
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
	if (Stop_Bits == 2)
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
	else if (Stop_Bits == 1)
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

#elif Parity_Type == OddParity
SET_BIT(UCSRC , UPM0);
SET_BIT(UCSRC , UPM1);

u16 UART_SendFrame_SW(u8 data)
{
	u16 Frame=0;
	u8 StopBits = 0 , Parityflag = 0;
	Frame = data << 1; // Start bit
	// Parity Check Bit:
	if (countSetBits(data) == EVEN && (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1))
	{
		// Frame = 00000101 0
		Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else if (countSetBits(data) == ODD && (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1))
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
	if (Stop_Bits == 2)
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
	else if (Stop_Bits == 1)
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

#endif
*/