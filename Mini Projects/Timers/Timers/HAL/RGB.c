/*
* RGB.c
*
* Created: 12/10/2023 2:57:23 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "RGB.h"
#include "RGB_Config.h"
#include "MemoryMap.h"

rgb_t RGB_LEDs[NO_OF_RGB_LEDs];

u8 Color_List[][3] ={	
	{254, 255, 255},        // WHITE
	{0  ,   0,   0},        // BLACK
	{254,   0,   0},        // RED
	{  0, 255,   0},        // GREEN
	{  0,   0, 255},        // BLUE
	{254, 255,   0},        // YELLOW
	{  0, 255, 255},        // CYAN
	{254,   0, 255},        // MAGENTA
	{254, 128, 128}			// LIGHT_RED

};

void RGB(u8 LED_Num , color_t color)
{
	RGB_LEDs[LED_Num].Red = Color_List[color][0];
	RGB_LEDs[LED_Num].Green = Color_List[color][1];
	RGB_LEDs[LED_Num].Blue = Color_List[color][2];
	
	RED_COLOR   = RGB_LEDs[LED_Num].Red;
	GREEN_COLOR = RGB_LEDs[LED_Num].Green;
	BLUE_COLOR  = RGB_LEDs[LED_Num].Blue;
	
	
}

void Set_PWM(u8 LED_Num, u8 Red_pin_Duty_Cycle, u8 Green_pin_Duty_Cycle, u8 Blue_pin_Duty_Cycle)
{
	RGB_LEDs[LED_Num].Red   = Red_pin_Duty_Cycle;
	RGB_LEDs[LED_Num].Green = Green_pin_Duty_Cycle;
	RGB_LEDs[LED_Num].Blue  = Blue_pin_Duty_Cycle;

	RED_COLOR   = RGB_LEDs[LED_Num].Red;       // Set OCR0 to adjust red duty cycle
	GREEN_COLOR = RGB_LEDs[LED_Num].Green;   // Set OCR1A to adjust green duty cycle
	BLUE_COLOR  = RGB_LEDs[LED_Num].Blue;     // Set OCR1B to adjust blue duty cycle
}
