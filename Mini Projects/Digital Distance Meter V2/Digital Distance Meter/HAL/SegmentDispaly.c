/*
* SegmentDispaly.c
*
* Created: 10/12/2023 2:54:39 AM
*  Author: Mohammed Khalaf
*/
#include "Utils.h"
#include "MemoryMap.h"
#include "stdTypes.h"
#include "SegmentDisplay.h"
#define F_CPU 8000000UL
#include <util/delay.h>

const u8 segmentPatterns[] = {
	0x3F, //0b00111111      0
	0x06, // 0b01011011     1
	0x5B, // 0b01011011     2
	0x4F, // 0b01001111     3
	0x66, // 0b01100110     4
	0x6D, // 0b01101101     5
	0x7D, // 0b01111101     6
	0x07, // 0b00000111     7
	0x7F, // 0b01101111     8
	0x6F, // 0b01101111     9
	0x00  // 0b00000000  // Off (all segments off)
};
// 7-segment patterns for hexadecimal digits 0 to F
const u8 hexPatterns[] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b00000000  // 0b00000000  // Off (all segments off)
};

//Two 7Segement Display to display numbers from 0 - 99
void segment_Display(u8 num)
{
	SEGMENT_PORT1 = segmentPatterns[num % 10];
	/*If we use Anode segment type:*/
	//SEGMENT_PORT = ~segmentPatterns[num / 10];
	SEGMENT_PORT2 = segmentPatterns[num / 10];
	/*If we use Anode segment type:*/
	//SEGMENT_PORT2 = ~segmentPatterns[num % 10];
}

void segment_Display_BCD(u8 num)  // 35
{
	u8 onesPattern = num % 10;
	u8 tensPattern = num/10;
	
	SEGMENT_PORT1 = onesPattern | tensPattern<<4;
	
}

void displayHexDigit(u8 num) {
	u8 n = hexPatterns[num];
	SEGMENT_PORT2 = n;
}
void displayHexDigit_BCD(u8 num) {
	u8 lower = num %16;
	u8 upper = num / 16;
	SEGMENT_PORT1 = lower | upper << 4;
}
void segment_Display_MLX(u8 num)
{
	u8 digitOne = num % 10;
	u8 digitTwo = num / 10;
	
	SET_BIT(MLX_SET_CLEARPORT , 0);
	SEGMENT_PORT1 = segmentPatterns[digitOne];
	CLEAR_BIT(MLX_SET_CLEARPORT , 1);
	// Delay for multiplexing
	_delay_ms(10);
	
	// Display digit 2
	
	SET_BIT(MLX_SET_CLEARPORT ,1);
	SEGMENT_PORT1 = segmentPatterns[digitTwo];
	CLEAR_BIT(MLX_SET_CLEARPORT , 0);

	// Delay for multiplexing
	_delay_ms(10);
}
void displayHexDigit_MLX(u8 num)
{
	u8 digitOne = num % 16;
	u8 digitTwo = num / 16;
	
	SET_BIT(PORTB , 6);
	SEGMENT_PORT2 = hexPatterns[digitOne];
	CLEAR_BIT(PORTB , 7);
	// Delay for multiplexing
	_delay_ms(10);
	
	// Display digit 2
	
	SET_BIT(PORTB ,7);
	SEGMENT_PORT2 = hexPatterns[digitTwo];
	CLEAR_BIT(PORTB , 6);

	// Delay for multiplexing
	_delay_ms(10);
}

void segment_Display_MLX_MultiDigits(u16 num)
{
	u8 digitOne = num % 10;
	u8 digitTwo = (num / 10) % 10;
	u8 digitThree = num / 100;
	
	SET_BIT(PORTD , 0);
	SET_BIT(PORTD , 1);
	SEGMENT_PORT1 = segmentPatterns[digitOne];
	CLEAR_BIT(PORTD , 2);
	_delay_ms(5);
	SET_BIT(PORTD , 2);
	SET_BIT(PORTD , 0);
	SEGMENT_PORT1 = segmentPatterns[digitTwo];
	CLEAR_BIT(PORTD , 1);
	_delay_ms(5);
	SET_BIT(PORTD , 1);
	SET_BIT(PORTD , 2);
	SEGMENT_PORT1 = segmentPatterns[digitThree];
	CLEAR_BIT(PORTD , 0);
	_delay_ms(5);
	
}

void init() {
	SEGMENT_DDR1 = 0xFF;
	SEGMENT_PORT1 = 0;
	SEGMENT_DDR2 = 0xFF;
	SEGMENT_PORT2 = 0;
}


void displayHexDigit_kit(u8 num) {
	u8 lower = num %16;
	u8 upper = num / 16;
	SET_BIT(PORTC , 6);
	PORTA = hexPatterns[lower]<<1;
	CLEAR_BIT(PORTC , 7);
	// Delay for multiplexing
	_delay_ms(10);
	SET_BIT(PORTC ,7);
	PORTA = hexPatterns[upper]<<1;
	CLEAR_BIT(PORTC , 6);
	// Delay for multiplexing
	_delay_ms(10);
}

void segment_Display_MLX_kit(u8 num)
{
	u8 digitOne = num % 10;
	u8 digitTwo = num / 10;
	
	SET_BIT(PORTC , 6);
	PORTA = segmentPatterns[digitOne]<<1;
	CLEAR_BIT(PORTC , 7);
	
	// Delay for multiplexing
	_delay_ms(10);

	// Display digit 2
	
	SET_BIT(PORTC ,7);
	PORTA = segmentPatterns[digitTwo]<<1;
	CLEAR_BIT(PORTC , 6);
	

	// Delay for multiplexing
	_delay_ms(10);
}
