/*
* UART_Config.c
*
* Created: 1/3/2024 11:39:27 PM
*  Author: Mohamed Khalaf
*/

#include "stdTypes.h"
#include "UART_Config.h"

#if Parity_Type == EvenParity
CLEAR_BIT(UCSRC , UPM0);
SET_BIT  (UCSRC , UPM1);

#elif Parity_Type == OddParity
SET_BIT(UCSRC , UPM0);
SET_BIT(UCSRC , UPM1);

#endif

// Stop bits
#if Stop_Bits == ONE
CLEAR_BIT(UCSRC , USBS);
#elif Stop_Bits == TWO
SET_BIT(UCSRC , USBS);
#endif