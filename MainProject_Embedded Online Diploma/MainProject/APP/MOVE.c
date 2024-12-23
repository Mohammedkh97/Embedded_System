 /*
* MOVE.c
*
* Created: 10/21/2023 1:13:32 AM
*  Author: Mohammed Khalaf
*/
#include "stdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_Interface.h"
#include "DIO_Config.h"
#include "MOVE.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void MOVE_Init()
{
	
}

void MOVE_Runnable(void)
{
	if (DIO_ReadPin1(Forward_Button) == LOW)
	{
		forward();
	}
	else if(DIO_ReadPin1(Right_Button) == LOW)
	{
		turnRight();
	}
	if(DIO_ReadPin1(Left_Button) == LOW)
	{
		turnLeft();
	}
	if(DIO_ReadPin1(Backward_Button) == LOW)
	{
		backward();
	}
	if(DIO_ReadPin1(Stop_Button) == LOW)
	{
		Stop();
	}
}

void forward(void)
{
	Stop();
	
	_delay_ms(50); // Adjust the delay to control motor speed
	
	Motor_CCW(F_R);
	Motor_CW(F_L);
	Motor_CCW(B_R);
	Motor_CW(B_L);
}

void turnRight(void)
{
	Stop();
	
	Motor_CW(F_L);
	Motor_CW(B_L);
	Motor_STOP(F_R);
	Motor_STOP(B_R);
	
}
void turnLeft(void)
{
	Stop();

	Motor_CW(F_R);
	Motor_CW(B_R);
	Motor_STOP(F_L);
	Motor_STOP(B_L);
}
void backward(void)
{
	
	Stop();

	_delay_ms(50);

	Motor_CW(F_R);
	Motor_CCW(F_L);
	Motor_CW(B_R);
	Motor_CCW(B_L);
}
void Stop()
{
	Motor_STOP(F_R);
	Motor_STOP(B_R);
	Motor_STOP(F_L);
	Motor_STOP(B_L);
}