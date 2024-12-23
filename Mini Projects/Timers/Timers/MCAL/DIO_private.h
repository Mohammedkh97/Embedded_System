/*
 * DIO_private.h
 *
 * Created: 10/17/2023 12:56:07 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


extern const DIO_PinStatus_t DIO_PinsStatusArr[TOTAL_PINS];
//static void DIO_initPin(DIO_Port_t port , u8 pin_num , DIO_PinStatus_t status);
static void DIO_initPin1(DIO_Pins_t pin , DIO_PinStatus_t status);

#endif /* DIO_PRIVATE_H_ */