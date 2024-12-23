/*
 * MOVE.h
 *
 * Created: 10/21/2023 1:13:14 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef MOVE_H_
#define MOVE_H_

#define F_R		M1
#define F_L		M2
#define B_R		M3
#define B_L		M4

#define Forward_Button    PINC0
#define Backward_Button   PINC1
#define Right_Button      PINC2
#define Left_Button       PINC3
#define Stop_Button       PINC4

void forward(void);
void turnRight(void);
void turnLeft(void);
void backward(void);
void Stop(void);


void MOVE_Runnable(void);




#endif /* MOVE_H_ */