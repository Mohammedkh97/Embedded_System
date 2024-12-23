/*
 * MainProject.c
 *
 * Created: 10/9/2023 1:44:16 AM
 * Author : Mohammed Khalaf
 */
#include "Utils.h"
#include "MemoryMap.h"
#include "stdTypes.h"

#define CLOCK 16
#define F_CPU 8000000UL
#include <util/delay.h>

// Task1:

int main(void)
{
    DDRA = 0xFF;
    PORTA = 0x01;
    volatile unsigned char value = 0;
    volatile char direction = 1; // 1 for forward, -1 for reverse
    u8 currentLED = 0;
    PORTB = 1;
    DDRB = 0xFF;
    while (1)
    {
        SET_BIT(value, j);
        PORTA = value;
        // delay_ms(5000);
        _delay_ms(300);
        CLEAR_BIT(PORTA, u8 currentLED = 0;);

        currentLED += direction;

        if (currentLED == 7)
        {
            direction = -1;
        }
        else if (currentLED == 0)
        {
            direction = currentLED;
        }
    }
}

int main(void)
{

    DDRA = 0xFF;  // Set PORTA as output
    PORTA = 0x00; // Turn off all LEDs initially

    DDRD = 0;     // Set PORTD as input
    PORTD = 0xFF; // Enable pull-up resistors on PORTD
    while (1)
    {
        for (u8 i = 0; i < 5; i++)
        {
            PORTA = 0xFF;
            _delay_ms(200);
            PORTA = 0;
            _delay_ms(200);
        }
        for (u8 i = 0; i < 5; i++)
        {
            PORTA = 0x0F;
            _delay_ms(200);
            PORTA = 0xF0;
            _delay_ms(200);
        }
        for (u8 i = 0; i < 5; i++)
        {
            PORTA = 0xCC; // 1001100
            _delay_ms(200);
            PORTA = 0x33; // 00110011
            _delay_ms(200);
        }
        for (u8 i = 0; i < 5; i++)
        {
            PORTA = 0xAA; // 10101010
            _delay_ms(200);
            PORTA = 0x55; // 01010101
            _delay_ms(200);
        }
    }

    return 0;
}

// Task2:
int main(void)
{
    u8 currentLED = 0;
    DDRA = 0xFF;  // Set PORTA as output
    PORTA = 0x00; // Turn off all LEDs initially

    DDRD = 0;     // Set PORTD as input
    PORTD = 0xFF; // Enable pull-up resistors on PORTD
    while (1)
    {
        if (!GET_BIT(PIND, 2))
        {

            while (!GET_BIT(PIND, 2))
            {
                currentLED++;
                if (currentLED >= 8)
                {
                    currentLED = 0;
                }
                SET_BIT(PORTA, currentLED);
                _delay_ms(100);
                PORTA = 0;
            }
        }
        else
        {
            SET_BIT(PORTA, currentLED);
        }
        if (!GET_BIT(PIND, 3))
        {
            while (!GET_BIT(PIND, 3))
            {
                currentLED--;
                if (currentLED == 255)
                {
                    currentLED = 7;
                }
                SET_BIT(PORTA, currentLED);

                _delay_ms(100);
                PORTA = 0;
            }
        }
        else
        {
            SET_BIT(PORTA, currentLED);
        }
    }

    return 0;
}

// Task3:

int main(void)
{
    u8 currentLED = 0;
    DDRA = 0xFF;  // Set PORTA as output
    PORTA = 0x00; // Turn off all LEDs initially

    DDRD = 0;     // Set PORTD as input
    PORTD = 0xFF; // Enable pull-up resistors on PORTD
    while (1)
    {
        if (!GET_BIT(PIND, 2)) // Check if the forward button is pressed
        {
            currentLED++;
            if (currentLED == 8)
            {
                currentLED = 0;
            }
            _delay_ms(10);
            while (!GET_BIT(PIND, 2))
                ;
            _delay_ms(10);
            PORTA = 0;
        }
        if (!GET_BIT(PIND, 3))
        {
            currentLED--;
            if (currentLED == 255)
            {
                currentLED = 7;
            }
            _delay_ms(10);
            while (!GET_BIT(PIND, 3))
                ;
            _delay_ms(10);
            PORTA = 0;
        }

        SET_BIT(PORTA, currentLED);
    }

    return 0;
}

// Task4:
int main(void)
{
    u8 currentLED = 0;
    DDRA = 0xFF;  // Set PORTA as output
    PORTA = 0x00; // Turn off all LEDs initially

    DDRD = 0;     // Set PORTD as input
    PORTD = 0xFF; // Enable pull-up resistors on PORTD
    while (1)
    {
        if (!GET_BIT(PIND, 2))
        {

            while (!GET_BIT(PIND, 2))
            {
                currentLED++;
                if (currentLED >= 8)
                {
                    currentLED = 0;
                }
                SET_BIT(PORTA, currentLED);
                _delay_ms(100);
                PORTA = 0;
            }
        }
        else
        {
            SET_BIT(PORTA, currentLED);
        }
        if (!GET_BIT(PIND, 3))
        {
            while (!GET_BIT(PIND, 3))
            {
                currentLED--;
                if (currentLED == 255)
                {
                    currentLED = 7;
                }
                SET_BIT(PORTA, currentLED);

                _delay_ms(100);
                PORTA = 0;
            }
        }
        else
        {
            SET_BIT(PORTA, currentLED);
        }
    }

    return 0;
}
// Task5:

int main(void)
{
	u8 currentLED = 0;
	u8 c = 0;
	u8 directionFlag = 1;
	DDRA = 0xFF; // Set PORTA as output
	PORTA = 0x00; // Turn off all LEDs initially

	DDRD = 0; // Set PORTD as input
	PORTD = 0xFF; // Enable pull-up resistors on PORTD

	while (1)
	{
		if (!GET_BIT(PIND, 2)) // Check if the button is pressed
		{
			if (c == 0)
			{
				c = 1;
				directionFlag ^= 1; // Toggle the direction on each button press
			}
		}
		else
		{
			c = 0;
		}

		if (directionFlag == 1) // Forward direction
		{
			CLEAR_BIT(PORTA, currentLED);
			currentLED++;
			if (currentLED >= 8)
			{
				currentLED = 0;
			}
			SET_BIT(PORTA, currentLED);
		}
		else if (directionFlag == 0) // Reverse direction
		{
			CLEAR_BIT(PORTA, currentLED);
			currentLED--;
			if (currentLED == 255)
			{
				currentLED = 7;
			}
			SET_BIT(PORTA, currentLED);
		}

		_delay_ms(300);
	}

	return 0;
}