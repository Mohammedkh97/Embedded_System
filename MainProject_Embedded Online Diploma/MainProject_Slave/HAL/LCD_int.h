/*
 * LCD_init.h
 *
 * Created: 10/24/2023 12:44:02 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_


void LCD_Init(void);
void write_instruction(u8 instruction);
void write_Data(u8 data);
void LCD_WriteChar(u8 ch);
void LCD_WriteStr(u8* str);
void LCD_WriteNumber(s32 num);
void LCD_Clear(void);

void LCD_Binary_Number_Display(s32 num);
void LCD_Hex_Number_Display(s32 num);
void LCD_ASCII_Number_Display(u8 ascii);
void LCD_WriteNumber_4Digits(u32 num);
/*
line: 1 - 2 
cell: 1 - 16
*/
void LCD_SetCursor(u8 line , u8 cell);
void LCD_WriteStringCursor(u8 line,u8 cell,u8*str);





#endif /* LCD_INIT_H_ */