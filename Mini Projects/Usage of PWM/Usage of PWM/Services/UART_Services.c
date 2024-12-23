
#include "stdTypes.h"
#include "MemoryMap.h"
#include "UART.h"
#include "Utils.h"
#include "UART_Services.h"
#include "UART_Config.h"


/* synch function */
void UART_SendString(u8*str)
{
	u8 i;
	for (i = 0 ; str[i] ; i++)
	{
		UART_SendData(str[i]);
	}
	str[i] =' ';
	UART_SendData(str[i]);
	// UART_SendData('\n');
}

void UART_ReceiveString(u8*str)
{	
	u8 i=0;
	str[i]=UART_ReceiveData();
	for (;str[i]!=0x0d;)  // 0x0d Enter char     0x0d = 13
	{
		i++;
		str[i]=UART_ReceiveData();	
	}
	str[i]=0;

}
void UART_ReceiveString_DockLight(u8*str)   // Using DockLight
{
	u8 i=0;
	str[i]=UART_ReceiveData();
	while (str[i] != 0x0D && str[i + 1] != 0x0A)  // 0x0d0a Enter char    
	{
		i++;
		str[i]=UART_ReceiveData();
	}
	str[i]=0;

}

void UART_SendNumber(u32 num)
{
	UART_SendData((u8)num);
	UART_SendData((u8)(num>>8));
	UART_SendData((u8)(num>>16));
    UART_SendData((u8)(num>>24));
	
	/*u8*p=&num;
	UART_SendData(p[0]);
	UART_SendData(p[1]);
	UART_SendData(p[2]);
	UART_SendData(p[3]);
	*/
}

/*
void UART_ReceiveNumber(u32*pnum)
{
	u32 num=0;
	u8 b1=UART_ReceiveData();
	u8 b2=UART_ReceiveData();
	u8 b3=UART_ReceiveData();
	u8 b4=UART_ReceiveData();
	
	num=(u32)b1|(u32)b2<<8|(u32)b3<<16|(u32)b4<<24;
	
	//u8*p=&num;
	//p[0]=UART_Receive();
	//p[1]=UART_Receive();
	//p[2]=UART_Receive();
	//p[3]=UART_Receive();
	
	
}*/

u32 UART_ReceiveNumber()
{
	u32 num=0;
	u8 b1=UART_ReceiveData();
	u8 b2=UART_ReceiveData();
	u8 b3=UART_ReceiveData();
	u8 b4=UART_ReceiveData();
	
	num=(u32)b1|(u32)b2<<8|(u32)b3<<16|(u32)b4<<24;
	
	/*u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	*/
	return num;
}



endian_t Endian_Check(void)
{
	u32 x=1;
	u8*p= (u8*)&x;
	if (*p==1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 endian_convert(u32 num)
{
	return  (num<<24)|(num>>24)|((num>>8)&(0x0000ff00))|((num<<8)&(0x00ff0000));	
	
	/*
	u8 *p = &num;
	u8 temp;
	temp = p[0];
	p[0] = p[3];
	p[3] = temp;
	
	temp = p[1];
	p[1] = p[2];
	p[2] = temp;
	
	return num;
	*/
}
u16 endian_convert_16(u16 num)
{
	return  (num<<8)|(num>>8);
}


void diagCallOut(u8*data)
{
	
	
}


void UART_SendStringCheckSum(u8*str)
{
	u8 len=0;
	u16 sum=0;
	for (len=0;str[len];len++);
	UART_SendData(len);
	for (len=0;str[len];len++)
	{
		UART_SendData(str[len]);
		sum+=str[len];
	}
	UART_SendData((u8)sum);
	UART_SendData((u8)(sum>>8));
}

u8 UART_ReceiveStringCheckSum(u8*str)
{
	// For Example: Str = "mohamed" 
	// len = 7     sum = 731 
	u8 i,len;
	
	u16 Calculated_sum = 0;
	u16 Received_sum = 0;
	len=UART_ReceiveData();
	// The two bytes of received sum:
	u8 byte1 = 0 , byte2 = 0; 
	for (i=0;i<len;i++)
	{
		str[i]=UART_ReceiveData();
		Calculated_sum = Calculated_sum + str[i];
	}
	str[i] = 0; 
	
	byte1=UART_ReceiveData();
	byte2=UART_ReceiveData();
	Received_sum=(u16)byte1|(u16)(byte2<<8); // 0000 0010 1101 1011
	
	if (Received_sum==Calculated_sum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static u8 *TX_Str;
static u8 *RX_Str;
static u8 flag=1;
//static u8 i=0;
void Tx_Function_Asynchronous(void)
{
	static u8 i=1;
	
	if (TX_Str[i] != 0)
	{
		UART_SendData_NO_BLOCK(TX_Str[i]);
		i++;
	}
	else
	{
		i = 1;
	}
}

void UART_SendStringAsynchronous(u8*str)  
{
	static u8 i=0;
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
	UART_SendData_NO_BLOCK(str[0]);
	TX_Str=str;
	
}


void UART_SendStringAsynchronous_NO_BLOCK(u8* str) // It considered Asynchronous Function due to not complete the task immediately once you pass the string
{
	static u8 i = 0;
	if (flag == 1)
	{
		if (str[i] !=0)
		{
			UART_SendData_NO_BLOCK(str[i]);
			i++;
		}
		flag = 0;
	}
	
}
void UART_Basic_Communication_Module_Init(void)
{
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
}

void UART_Basic_Communication_Module_SendString(u8* str)
{
	TX_Str = str;
}

void UART_Basic_Communication_Module_Runnable(void)
{
	static u8 i = 0;
	if (flag == 1)
	{
		if (TX_Str[i] !=0)
		{
			UART_SendData_NO_BLOCK(TX_Str[i]);
			i++;
		}
		flag = 0;
	}
}

void Rx_Function_Asynchronous()
{
	static u8 i = 0;
	
	RX_Str[i] = UART_ReceiveData_NO_BLOCK();
	i++;
	if (i>20)
	{
		i = 0;
	}
	 
}

void UART_Receive_Asynchronous(u8* str)
{
	UART_RX_Interrupt_Enable();
	UART_RX_SetCallback(Rx_Function_Asynchronous);
	RX_Str = str;
}

/*

static u8*TX_Str[10];
static u8 flag=1;
static u8 i=0;
void Tx_Function_Asynchronous(void)
{
	static u8 j=1;
	static u8 i=0;
	if (TX_Str[i][j])
	{
		UART_SendData_NO_BLOCK(TX_Str[i][j]);
		j++;
	}
	else
	{
		j=1;
		i++;
	}
}


void UART_SendStringAshync(u8*str)
{
	static u8 i=0;
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
	UART_SendData_NO_BLOCK(str[0]);
	TX_Str[i]=str;
	
	i++;
}
*/



/*
void func_tx2(void)
{
	flag=1;
}

void UART_SendStringInit(void)
{
	UART_TX_SetCallBack(func_tx2);
	UART_TX_InterruptEnable();
}

void UART_SendStringRunnable(void)
{
	static u8 j=0;
	static u8 i=0;
	if (flag==1)
	{
		if (TX_Str[i][j])
		{
			UART_SendNoBlock(TX_Str[i][j]);
			j++;
		}
		else
		{
			j=0;
			i++;
		}
		flag=0;
	}
		
}

void UART_SendStringSetter(u8*str)
{
	TX_Str[i]=str;
	i++;
}

u8* RXStr;
u8 changeflag;
static void func_Rx(void)
{
	static u8 i=0;
	if (changeflag==1)
	{
		i=0;
		changeflag=0;
	}
	RXStr[i]=UART_ReceiveNoBlock();
	i++;
}
void UART_ReceiveStringAshync(u8*str)
{
	UART_RX_SetCallBack(func_Rx);
	
	UART_RX_InterruptEnable();
	if (str!=RXStr)
	{
		changeflag=1;
	}
	RXStr=str;
}


u8 RX_Buffer1[8];
u8 RX_Buffer2[8];
static u8 Bufferflag=0;
u8 readyflag=0;
static void func_Rx2(void)
{
	static u8 i=0;
	
	if (Bufferflag==0)
	{
		RX_Buffer1[i]=UART_ReceiveNoBlock();
	}
	else
	{
		RX_Buffer2[i]=UART_ReceiveNoBlock();
	}
	i++;
	if (i==8)
	{
		i=0;
		readyflag=1;
		Bufferflag^=1;
	}
	
}

void UART_BufferInit(void)
{
	UART_RX_SetCallBack(func_Rx2);
	
	UART_RX_InterruptEnable();
}

u8 UART_BufferGetter(u8*str)
{
	u8 i;
	if (readyflag==0)
	{
		return 0;
	}
	for (i=0;i<8;i++)
	{
		if (Bufferflag==0)
		{
			str[i]=RX_Buffer2[i];
		}
		else
		{
			str[i]=RX_Buffer1[i];
		}
	}
	readyflag=0;
	return 1;
}

*/

u16 UART_SendFrame_SW(u8 data)
{
	u16 Frame=0;
	u8 Parityflag = 0, stop_bits = Stop_Bits;
	Frame = data << 1; // Start bit
	// Parity Check Bit:
	if (countSetBits(data) == EVEN && (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1))  // the Second part can be deleted as you can set config file .h and .c
	{
		// Frame = 00000101 0
		Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else if (countSetBits(data) == ODD && (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)) // the Second part can be deleted as you can set config file .h and .c
	{
		Frame = Frame | (ODD << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else
	{
		Parityflag = 0;
		Frame = Frame;
	}
	// Stop Bit:
	if (stop_bits == 2 && (GET_BIT(UCSRC , USBS)))
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (3 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (3 << (0 + Data_Length + Start_Bit)) ;
		}
		
	}
	else if (stop_bits == 1 && (!GET_BIT(UCSRC , USBS)))  // the Second part can be deleted as you can set config file .h and .c
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (1 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (1 << (0 + Data_Length + Start_Bit)) ;
		}
	}
	return Frame;
}


// Function to count the number of set bits  (ONES)
u8 countSetBits(u16 num)
{
	u8 count = 0;
	while (num) {
		count += num & 1;  // Add the last bit to the count if it is 1
		num >>= 1;         // Right shift the number to remove the processed bit
	}
	
	if (count % 2 == 0)
	{
		return EvenParity;
	}
	else
	return OddParity;
}

Parity_t UART_CheckParity(u8 data)
{
	if (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)
	{
		return ODD;
	}
	else if (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1)
	{
		return EVEN;
	}
}