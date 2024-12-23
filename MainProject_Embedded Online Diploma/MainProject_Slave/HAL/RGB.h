/*
 * RGB.h
 *
 * Created: 12/10/2023 2:57:04 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef RGB_H_
#define RGB_H_

#include "RGB_Config.h"



typedef enum{
	
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

typedef struct rgb_color_array
{
	rgb_t colors[Total_of_Colors];
} color_list_t;

void RGB(char LED_Num , color_t Color);
void Set_PWM(char Red_pin , char Green_pin , char Blue_pin);




#endif /* RGB_H_ */