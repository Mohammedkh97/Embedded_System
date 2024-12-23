/*
 * SPI.c
 *
 * Created: 1/12/2024 1:02:43 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "MemoryMap.h"
#include "SPI.h"

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
u8 SPI_Receive_Periodic(u8* pdata) // This function is only for SPI SLAVE
{
	if (!GET_BIT(SPDR , SPIF))
	{
		*pdata = SPDR;   
		return 1;
	}
	else 
	return 0;
}