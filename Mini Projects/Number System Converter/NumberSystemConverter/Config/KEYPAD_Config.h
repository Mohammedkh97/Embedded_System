/*
* KEYPAD_Config.h
*
* Created: 10/31/2023 4:58:38 PM
*  Author: mohammed Khalaf
*/


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*#define FIRST_OUTPUT    PINC4

#define FIRST_INPUT     PINC0*/

/*KIT*/
#define FIRST_OUTPUT    PINB4

#define FIRST_INPUT     PIND2

#define ROW		4
#define COL		4

#define NO_KEY  'X'

#ifdef  KEYPAD_PROG
u8 KeysArray[ROW][COL] = {	{'7' , '8' , '9' , 'A'},
							{'4' , '5' , '6' , 'B'},
							{'1' , '2' , '3' , 'C'},
							{'Q' , '0' , '=' , 'D'}};

#endif



#endif /* KEYPAD_CONFIG_H_ */