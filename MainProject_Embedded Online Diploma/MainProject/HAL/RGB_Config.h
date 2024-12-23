/*
 * RGB_Config.h
 *
 * Created: 12/10/2023 2:58:26 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef RGB_CONFIG_H_
#define RGB_CONFIG_H_

#define RED_COLOR     OCR0
#define GREEN_COLOR   OCR1A
#define BLUE_COLOR    OCR1B

#define NO_OF_RGB_LEDs    1
#define Total_of_Colors   7
#define RGB_NUM           0

/*Configure pins for RGB Duty Cycle in RGB_Set_PWM function  */
#define RED_PIN_DUTY_CYCLE			50 
#define GREEN_PIN_DUTY_CYCLE		50
#define BLUE_PIN_DUTY_CYCLE			20

#endif /* RGB_CONFIG_H_ */