/*
* KEYPAD_Config.h
*
* Created: 10/31/2023 4:58:38 PM
*  Author: mohammed Khalaf
*/


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define FIRST_OUTPUT    PINC4

#define FIRST_INPUT     PINC0

#define ROW		4
#define COL		4

#define NO_KEY  'X'

#ifdef  KEYPAD_PROG
u8 KeysArray[ROW][COL] = {	{'7' , '8' , '9' , '/'},
							{'4' , '5' , '6' , '*'},
							{'1' , '2' , '3' , '-'},
							{'C' , '0' , '=' , '+'}};

#endif



#endif /* KEYPAD_CONFIG_H_ */