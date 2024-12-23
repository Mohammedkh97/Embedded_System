/*
 * TempFilter.c
 *
 * Created: 11/12/2023 2:47:54 AM
 *  Author: Mohammed Khalaf
 */ 
#include "stdTypes.h"
#include "Sensors_int.h"


u16 Temp[10];
u16 UnfilteredTemp;
u16 FilteredTemp;
u8 AvgFlag;

void Temp_init()
{
	
}
void Temp_Runnable()
{
	static u8 i = 0;
	u16 total = 0;
	Temp[i]= SENSORS_LM35_ReadTemp(); // Temp in C*10
	
	UnfilteredTemp = Temp[i];
	i++;
	if (i == 10)
	{
		i = 0;
		AvgFlag = 1;
	}
	
	if(AvgFlag == 1)
	{
		for (u8 j = 0 ; j < 10 ; j++)
		{
			total = total + Temp[j];
		}
		FilteredTemp = total/10;
	}
	
	FilteredTemp = (total + Temp[i-1]) / 10;
}

u16 Temp_Get_Filtered()
{
	return FilteredTemp;
}

u16 Temp_Get_Unfiltered()
{
	return UnfilteredTemp;
}