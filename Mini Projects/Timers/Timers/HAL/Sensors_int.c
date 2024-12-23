/*
 * Sensors_int.c
 *
 * Created: 11/10/2023 8:49:30 PM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "ADC_int.h"
#include "Sensors_int.h"
#include "Sensors_Config.h"


u16 SENSORS_LM35_ReadTemp()
{
	u16 temp = 0;
	u16 volt = ADC_ReadVolt(LM35); // Volt in mV
	/*LM35 Sensor can read 0.5 C degree but there is no float number in our system*/
	/*We can amplify the value of volt by setting it (volt*10)   */
	//temp = volt / 10; // From LM35 Datasheet, Every 10mV = 1C degree
	temp = volt;  // Here, we can say that Temp in (C*10)
	
	return temp;
}

u16 SENSORS_MPX4115_ReadPressure()
{
	u16 pressure = 0;
	//u16 volt = ADC_ReadVolt(MPX4115);
	u16 ADCRead = ADC_Read(MPX4115);	
	pressure = (((u32)1000*(ADCRead - 41))/983) + 150;
	
	return pressure;
	
}