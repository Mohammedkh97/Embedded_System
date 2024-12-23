/*
 * RGB_Application_File.c
 *
 * Created: 12/10/2023 2:57:23 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "RGB.h"
#include "RGB_Config.h"
#include "MemoryMap.h"
#include "Timers.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"

#define F_CPU 8000000UL
#include <util/delay.h>

static u8 Selected_RGB_LED;
static u8 rgb_num = 0;
static u8 Get_RGB_Color = 0;
color_t RGB_color;
u8 shape[] = {
  0x10,
  0x18,
  0x0C,
  0x06,
  0x0C,
  0x18,
  0x10,
  0x00
  };

void RGB_App_init()
{
	TIMER0_Init(TIMER0_FASTPWM_MODE , TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_CLEAR);
	Timer1_OCRB1Mode(OCRB_CLEAR);
	//TIMER0_OC0Mode(OC0_CLEAR);
	TIMER0_OC0_PWM_Mode(OC0_CLEAR);
	Timer1_Set_ICR1_Value(256);
}
u8 RGB_Select(void)
{
	u8 EnterFlag = 0;
	LCD_Clear();
	LCD_Goto_WriteString(1,1,(u8*)" RGB Light Show");
	//LCD_Draw_Character(shape);
	//_delay_ms(1000);
	LCD_Clear();
	LCD_Goto_WriteString(2,1, (u8*)"   Please Select");
	LCD_Goto_WriteString(3,1, (u8*)" LED from RGB List");
	
	while(EnterFlag == 0)
	{
		rgb_num = KEYPAD_GetKey();
		if ((rgb_num >= '1' && rgb_num <= '7') && rgb_num != NO_KEY)
		{
			// Get the RGB LED from RGB List as an integer number:
			Selected_RGB_LED = (rgb_num - '0') - 1;
			LCD_Goto_WriteNumber(4,1,Selected_RGB_LED);
			EnterFlag = 1;
		}
	}
	return rgb_num;
}

void RGB_Color_Selection(void)
{
	u8 EnterFlag = 0;
	_delay_ms(2000);
	LCD_Clear();
	LCD_Goto_WriteString(1,1, (u8*)"1. WHITE 2. BLACK");
	LCD_Goto_WriteString(2,1, (u8*)"3. RED   4. GREEN");
	LCD_Goto_WriteString(3,1, (u8*)"5. BLUE  6. YELLOW");
	LCD_Goto_WriteString(4,1, (u8*)"7. CYAN  8. MAGENTA");
	while(EnterFlag == 0)
	{
		Get_RGB_Color = KEYPAD_GetKey();
		if (Get_RGB_Color >= '1' && Get_RGB_Color <= '8' && Get_RGB_Color != NO_KEY)
		{
			// Get the RGB LED Color as RGB Color List arrangement:
			RGB_color = (Get_RGB_Color - '0') - 1;
			/*LCD_Goto_WriteNumber(4,1,RGB_color);*/
			EnterFlag = 1;
		}
	}
	LCD_Clear();
	LCD_Goto_WriteNumber(1,1,Selected_RGB_LED);
	LCD_Goto_WriteNumber(2,1,RGB_color);
	RGB(Selected_RGB_LED , RGB_color);
}
void RGB_Runnable()
{
	
}