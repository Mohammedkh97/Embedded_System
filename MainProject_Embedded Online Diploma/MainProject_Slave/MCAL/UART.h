/*
 * UART.h
 *
 * Created: 12/21/2023 2:20:48 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UART_H_
#define UART_H_



void UART_init(void);
void UART_SendData(u8 data);
u8 UART_ReceiveData(void);
u8 UART_ReceiveData_Periodic(u8 *data);

void UART_SendData_NO_BLOCK(u8 data);
u8 UART_ReceiveData_NO_BLOCK();
void UART_RX_Interrupt_Enable(void);
void UART_RX_Interrupt_Disable(void);
void UART_TX_Interrupt_Enable(void);
void UART_TX_Interrupt_Disable(void);

void UART_RX_SetCallback(void(*LocalFptr)(void));

void UART_TX_SetCallback(void(*LocalFptr)(void));


#endif /* UART_H_ */