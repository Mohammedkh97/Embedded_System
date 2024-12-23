/*
 * AppFunctions.h
 *
 * Created: 11/7/2023 12:07:22 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef APPFUNCTIONS_H_
#define APPFUNCTIONS_H_


void decimalToBinary(u32 Num);
void decimalToHex(s32 num);
s32 binaryToDecimal(u8* binary);
void binaryToHex(u8* binary);
u32 HexToDecimal(u8 hexChar);
s32 HexStringToDecimal(u8* hexString);

void delay(u8 seconds);



#endif /* APPFUNCTIONS_H_ */