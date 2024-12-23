/*
 * Ultrasoinc.h
 *
 * Created: 12/13/2023 1:09:06 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef ULTRASOINC_H_
#define ULTRASOINC_H_




typedef enum
{
	ULTRASONIC_1 = PIND5,
	ULTRASONIC_2 = PINC2,
	ULTRASONIC_3 = PINC3,
	ULTRASONIC_4 = PINC4
	
}Ultrasonic_Trigger_t;

typedef struct
{
	Ultrasonic_Trigger_t US;
}Ultrasonic_t;

void Ultrasonic_init();
u8 Ultrasonic_Get_Distance(Ultrasonic_Trigger_t US1);


#endif /* ULTRASOINC_H_ */