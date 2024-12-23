/*
 * MOTOR_Interface.h
 *
 * Created: 10/20/2023 6:46:32 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4
	}motor_t;
void Motor_CW(motor_t motor);
void Motor_CCW(motor_t motor);
void Motor_STOP(motor_t motor);
#endif /* MOTOR_INTERFACE_H_ */