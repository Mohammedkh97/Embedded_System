/*
 * segmentDisplay.h
 *
 * Created: 10/12/2023 3:13:03 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef SEGMENTDISPLAY_H_
#define SEGMENTDISPLAY_H_

#define SEGMENT_PORT1 PORTC
#define SEGMENT_DDR1  DDRC
#define SEGMENT_PORT2 PORTD
#define SEGMENT_DDR2  DDRD

#define MLX_SET_CLEARPORT PORTD


void init();
void segment_Dispaly(u8 num);
void displayHexDigit(u8 num);
void segment_Dispaly_BCD(u8 num);
void segment_Display_MLX(u8 num);
void displayHexDigit_MLX(u8 num);
void displayHexDigit_BCD(u8 num);
void segment_Display_MLX_MultiDigits(u16 num);

/************************************************************************/
/*                         KIT Prototypes:                                                                     */
/************************************************************************/
void displayHexDigit_kit(u8 num);
void segment_Display_MLX_kit(u8 num);


#endif /* SEGMENTDISPLAY_H_ */