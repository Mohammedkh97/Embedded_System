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




#endif /* MEMORYMAP_H_ */