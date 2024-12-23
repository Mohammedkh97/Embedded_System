/*
 * MemoryMap.h
 *
 * Created: 10/10/2023 4:40:43 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

#define PORTA (*(volatile unsigned char*)0x3B)
#define DDRA (*(volatile unsigned char*)0x3A)
#define PINA (*(volatile unsigned char*)0x39)

#define PORTB (*(volatile unsigned char*)0x38)
#define DDRB (*(volatile unsigned char*)0x37)
#define PINB (*(volatile unsigned char*)0x36)

#define PORTC (*(volatile unsigned char*)0x35)
#define DDRC  (*(volatile unsigned char*)0x34)
#define PINC  (*(volatile unsigned char*)0x33)

#define PORTD (*(volatile unsigned char*)0x32)
#define DDRD (*(volatile unsigned char*)0x31)
#define PIND (*(volatile unsigned char*)0x30)

/* ADC_Registers */
#define ADMUX (*(volatile unsigned char*)0x27)

#define ADLAR 5 // Mode of ADC Read ADLAR = 0 or ADLAR = 1
#define REFS0 6
#define REFS1 7


#define ADCSRA (*(volatile unsigned char*)0x26)
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7

#define ADCL (*(volatile unsigned char*)0x24)
#define ADCH (*(volatile unsigned char*)0x25)


// Make sure the two register ADCL, ADCH are in row 
// so that we create ne to get the two value of ADC registers 

#define ADC (*(volatile unsigned short*)0x24) // optional




#endif /* MEMORYMAP_H_ */