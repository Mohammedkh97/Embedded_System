/*
 * SPI.h
 *
 * Created: 1/12/2024 1:03:11 AM
 *  Author: MohamMed Khalaf
 */ 


#ifndef SPI_H_
#define SPI_H_

/*#define MASTER 0
#define SLAVE  1

#define SPI_MODE     MASTER*/


typedef enum
{
	MASTER,
	SLAVE
	
}SPI_Mode_t;

void SPI_init(SPI_Mode_t mode);
u8 SPI_Send_Receive(u8 data);
void SPI_Send_No_Block(u8 data);
u8 SPI_Send_Receive_With_runtime_out(u8 data , u8* pData , u16 set_Time);

#endif /* SPI_H_ */