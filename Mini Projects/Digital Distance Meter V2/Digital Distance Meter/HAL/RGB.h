/*
 * RGB.h
 *
 * Created: 12/10/2023 2:57:04 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef RGB_H_
#define RGB_H_

#include "RGB_Config.h"



typedef enum
{
	WHITE ,
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	MAGENTA,
	LIGHT_RED
}color_t;

typedef struct color
{
	char Red;
	char Green;
	char Blue;

} rgb_t;


void RGB(u8 LED_Num , color_t color);
void Set_PWM(u8 LED_Num, u8 Red_pin_Duty_Cycle, u8 Green_pin_Duty_Cycle, u8 Blue_pin_Duty_Cycle);




#endif /* RGB_H_ */