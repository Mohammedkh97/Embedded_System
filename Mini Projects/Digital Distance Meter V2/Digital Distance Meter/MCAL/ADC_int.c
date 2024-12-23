/*
* ADC_int.c
*
* Created: 11/8/2023 3:53:51 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "ADC_int.h"
#define  F_CPU 8000000
#include <util/delay.h>

u8 BusyFlag;
void ADC_init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	/* Clock*/
	/*VREF*/
	switch(vref)
	{
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	ADCSRA&=0XF8;//0B11111000
	scaler&=0X07;//0B00000111
	ADCSRA|=scaler;
	
	
	/* ADC enable*/
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_t ch)
{
	/* select ch*/
	ADMUX&=0XE0;//0B11100000
	ADMUX|=ch;
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/* wait until ADC end conversion*/  // until ADSC is cleared ADSC ==> 0
	//_delay_ms(1);
	while(GET_BIT(ADCSRA,ADSC));// busy wait or blocking
	/* read register*/
	
	//return (ADCH<<8)|(ADCL);
	return ADC;
}


u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt=((u32)5000*adc)/1024;
	return volt;
	
}

void ADC_StartConversion(ADC_Channel_t ch )
{
	if (BusyFlag == 0)
	{
		ADMUX&=0XE0;//0B11100000
		ADMUX|=ch;
		/* start conversion*/
		SET_BIT(ADCSRA,ADSC);
		
		BusyFlag = 1;
	}

}
u16 ADC_GetRead()
{
	while(GET_BIT(ADCSRA,ADSC));// busy wait or blocking

	//return (ADCH<<8)|(ADCL);
	return ADC;
}

u8 ADC_GetReadPeriodic(u16* pData) //Polling
{
	if(GET_BIT(ADCSRA,ADSC))
	{
		return 0;
	}
	else
	{
		*pData = ADC;
		BusyFlag = 0;
		return 1;
	}
}

