/*
* DIO.c
*
* Created: 10/17/2023 12:54:34 AM
*  Author: Mohammed Khalaf
*/
#include "MemoryMap.h"
#include "stdTypes.h"
#include "DIO_interface.h"
#include "Utils.h" // MCAL needs Utils file

void DIO_initPin1(DIO_Pins_type pin, DIO_PinStatus_type status)
{
	DIO_Port_type port;
	u8 pin_num;

	port = (DIO_Port_type)(pin / 8);
	pin_num = pin % 8;

	switch (status)
	{
		case OUTPUT:
		switch (port)
		{
			case PA:
			SET_BIT(DDRA, pin_num);
			CLEAR_BIT(PORTA, pin_num);
			break;
			case PB:
			SET_BIT(DDRB, pin_num);
			CLEAR_BIT(PORTB, pin_num);
			break;
			case PC:
			SET_BIT(DDRC, pin_num);
			CLEAR_BIT(PORTC, pin_num);
			break;
			case PD:
			SET_BIT(DDRD, pin_num);
			CLEAR_BIT(PORTD, pin_num);
			break;
		}
		break;
		case INFREE:
		switch (port)
		{
			case PA:
			CLEAR_BIT(DDRA, pin_num);
			CLEAR_BIT(PORTA, pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB, pin_num);
			CLEAR_BIT(PORTB, pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC, pin_num);
			CLEAR_BIT(PORTC, pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD, pin_num);
			CLEAR_BIT(PORTD, pin_num);
			break;
		}
		break;
		case INPULL:
		switch (port)
		{
			case PA:
			CLEAR_BIT(DDRA, pin_num);
			SET_BIT(PORTA, pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB, pin_num);
			SET_BIT(PORTB, pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC, pin_num);
			SET_BIT(PORTC, pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD, pin_num);
			SET_BIT(PORTD, pin_num);
			break;
		}
		break;
	}
}


void DIO_WritePin1(DIO_Pins_type pin, DIO_PinVoltage_type volt)
{
	DIO_Port_type port;
	u8 pin_num;

	port = (DIO_Port_type)(pin / 8);
	pin_num = pin % 8;

	if (volt == HIGH)
	{
		switch (port)
		{
			case PA:
			SET_BIT(PORTA, pin_num);
			break;
			case PB:
			SET_BIT(PORTB, pin_num);
			break;
			case PC:
			SET_BIT(PORTD, pin_num);
			break;
			case PD:
			SET_BIT(PORTD, pin_num);
			break;
		}
	}
	else if (volt == LOW)
	{
		switch (port)
		{
			case PA:
			CLEAR_BIT(PORTA, pin_num);
			break;
			case PB:
			CLEAR_BIT(PORTB, pin_num);
			break;
			case PC:
			CLEAR_BIT(PORTD, pin_num);
			break;
			case PD:
			CLEAR_BIT(PORTD, pin_num);
			break;
		}
	}
}

DIO_PinVoltage_type DIO_ReadPin1(DIO_Pins_type pin)
{
	DIO_Port_type port;
	u8 pin_num;
	DIO_PinVoltage_type status;

	port = (DIO_Port_type)(pin / 8);
	pin_num = pin % 8;

	switch (port)
	{
		case PA:
		status = GET_BIT(PA, pin_num);
		break;
		case PB:
		status = GET_BIT(PB, pin_num);
		break;
		case PC:
		status = GET_BIT(PC, pin_num);
		break;
		case PD:
		status = GET_BIT(PD, pin_num);
		break;
	}
	return status;
}
