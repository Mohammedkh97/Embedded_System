/*
 * SERVO_int.c
 *
 * Created: 12/8/2023 2:13:43 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "MemoryMap.h"
#include "SERVO_int.h"
#include "Servo_Config.h"

void SERVO_WriteAngle(u8 angle)
{
	SERVO_PWM_PIN = (((u32)1000*angle) / 180) + 999;  
	// 999 ==> Refer to Zero when angle = 0 as OCR Range -1000 to 1000 == 2000
}