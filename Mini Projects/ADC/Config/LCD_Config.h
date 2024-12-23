/*
* LCD_Config.h
*
* Created: 10/24/2023 12:48:43 PM
*  Author: Mohammed Khalaf
*/


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* _4_BIT MODE, _8_BIT MODE */

#define _4_BIT     1
#define _8_BIT     2

#define LCD_MODE   _4_BIT

/*
#define RS     PIND5
#define EN     PIND7

#define D4     PIND0
#define D5     PIND1
#define D6     PIND2
#define D7     PIND3
*/

/*KIT Connections */
#define D4     PINA3
#define D5     PINA4
#define D6     PINA5
#define D7     PINA6

#define RS     PINA1
#define EN     PINA2


#define LCD_PORT PA




/*#if LCD_MODE == _4_BIT

#define RS    PIND5
#define EN    PIND7

#define D7     PIND3
#define D6     PIND2
#define D5     PIND1
#define D4     PIND0

#elif LCD_MODE _8_BIT

#define RS    PINB1
#define EN    PINB0

#define LCD_PORT PA
#endif*/




// Config for 4-bit LCD






#endif /* LCD_CONFIG_H_ */