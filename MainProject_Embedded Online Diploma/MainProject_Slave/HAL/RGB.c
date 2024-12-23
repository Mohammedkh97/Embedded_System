/*
 * RGB.c
 *
 * Created: 12/10/2023 2:57:23 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "RGB.h"
#include "ADC_int.h"
#include "RGB_Config.h"
#include "MemoryMap.h"


rgb_t Color_List[NO_OF_RGB_LEDs][Total_of_Colors] = {
	{{255, 0,  0},        // RED
	{0,   255, 0},        // GREEN
	{0,   0, 255},        // BLUE
	{255, 255, 0},        // YELLOW
	{0, 255, 255},        // CYAN
	{255, 0, 255},        // MAGENTA
	{255, 128, 128} }     // LIGHT_RED



};

	
void RGB(char LED_Num , color_t color)
{
	RED_COLOR   = Color_List[LED_Num][color].Red;
	GREEN_COLOR = Color_List[LED_Num][color].Green;
	BLUE_COLOR  = Color_List[LED_Num][color].Blue;
	
}

void Set_PWM(char Red_pin_Duty_Cycle , char Green_pin_Duty_Cycle , char Blue_pin_Duty_Cycle)
{
		
		RED_COLOR = Red_pin_Duty_Cycle;			// Set OCR0 to adjust duty cycle

		GREEN_COLOR = Green_pin_Duty_Cycle;		// Set OCR1A to adjust duty cycle

		BLUE_COLOR = Blue_pin_Duty_Cycle;		// Set OCR1B to adjust duty cycle
}
