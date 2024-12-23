

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

typedef enum
{
	LITTLE,
	BIG
}endian_t;

typedef enum
{
	EVEN = 0,
	ODD,
	NO_Parity
}Parity_t;




void UART_SendString(u8*str);
void UART_ReceiveString(u8*str);
void UART_ReceiveString_DockLight(u8*str);
void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber();

void UART_SendStringCheckSum(u8*str);
u8 UART_ReceiveStringCheckSum(u8*str);

void UART_SendStringAsynchronous(u8*str);
void UART_SendStringAsynchronous_NO_BLOCK(u8* str);

void UART_Basic_Communication_Module_Init(void);
void UART_Basic_Communication_Module_SendString(u8* str);
void UART_Basic_Communication_Module_Runnable(void);

u8 UART_BufferGetter(u8*str);

endian_t Endian_Check(void);

u16 UART_SendFrame_SW(u8 data);
u8 countSetBits(u16 num);
Parity_t UART_CheckParity(u8 data);

#endif /* UART_SERVICES_H_ */