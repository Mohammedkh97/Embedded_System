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


#endif /* SPI_H_ */