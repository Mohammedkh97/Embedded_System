/*
* MOTOR_Interface.c
*
* Created: 10/20/2023 6:47:04 AM
*  Author: Mohammed Khalaf
*/
#include "stdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Config.h"

void Motor_CW(motor_t motor)
{
	switch (motor)
	{
		case M1:
		DIO_WritePin1(M1_IN1 , HIGH);
		DIO_WritePin1(M1_IN2 , LOW);
		break;
		case M2:
		DIO_WritePin1(M2_IN1 , HIGH);
		DIO_WritePin1(M2_IN2 , LOW);
		break;
		case M3:
		DIO_WritePin1(M3_IN1 , HIGH);
		DIO_WritePin1(M3_IN2 , LOW);
		break;
		case M4:
		DIO_WritePin1(M3_IN1 , HIGH);
		DIO_WritePin1(M3_IN2 , LOW);
		break;
	}
	
}
void Motor_CCW(motor_t motor)
{
	switch (motor)
	{
		case M1:
		DIO_WritePin1(M1_IN1 , LOW);
		DIO_WritePin1(M1_IN2 , HIGH);
		break;
		
		case M2:
		DIO_WritePin1(M2_IN1 , LOW);
		DIO_WritePin1(M2_IN2 , HIGH);
		break;
		
		case M3:
		DIO_WritePin1(M3_IN1 , LOW);
		DIO_WritePin1(M3_IN2 , HIGH);
		break;
		
		case M4:
		DIO_WritePin1(M3_IN1 , LOW);
		DIO_WritePin1(M3_IN2 , HIGH);
		break;
	}
}

void Motor_STOP(motor_t motor)
{
	switch (motor)
	{
		case M1:
		DIO_WritePin1(M1_IN1 , LOW);
		DIO_WritePin1(M1_IN2 , LOW);
		break;
		case M2:
		DIO_WritePin1(M2_IN1 , LOW);
		DIO_WritePin1(M2_IN2 , LOW);
		break;
		case M3:
		DIO_WritePin1(M3_IN1 , LOW);
		DIO_WritePin1(M3_IN2 , LOW);
		break;
		case M4:
		DIO_WritePin1(M3_IN1 , LOW);
		DIO_WritePin1(M3_IN2 , LOW);
		break;
	}
}