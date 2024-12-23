/*
 * SPI.c
 *
 * Created: 1/12/2024 1:02:43 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "MemoryMap.h"
#include "SPI.h"
#include "Utils.h"

#define CLOCK  16
#define F_CPU 8000000UL
#include <util/delay.h>

void SPI_init(SPI_Mode_t mode)
{
	// SPI Enable:
	
	SET_BIT(SPCR , SPE);
	
	if (mode == MASTER)
	{
		// By default clk 2MHz  ( Freq / 4 = 8 / 4) :  ====> SPI2x  0   SPR1  0   SPR0  0    
		//  
		SET_BIT(SPCR , MSTR);	
	}
	else if (mode == SLAVE) 
	{
		CLEAR_BIT(SPCR , MSTR);
	}
}


u8 SPI_Send_Receive(u8 data)
{
	SPDR = data;
	while (!GET_BIT(SPDR , SPIF));  // Busy wait for the SPI Flag to be set

	return SPDR;
}

void SPI_Send_No_Block(u8 data)
{
	SPDR = data;
}

u8 SPI_Send_Receive_With_runtime_out(u8 data , u8* pData , u16 set_Time)  // This function is ONLY for SPI MASTER
{
	u16 counter = 0 ;// Comparator with the set runtime out 
	SPDR = data;
	while(!GET_BIT(SPSR ,SPIF) && counter < set_Time)
	{
		counter++;
		_delay_us(1);
	}
	if (counter < set_Time)
	{
		*pData = SPDR;
		return 1;
	}
	else
	{
		return 0;
	}
}


