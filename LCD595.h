/*
  RH Electronics 595 LCD
  June 2018
*/
#ifndef LCD595_h
#define LCD595_h

#include "Arduino.h"

class LCD595{

  public:
    LCD595(byte dataPin, byte clockPin, byte latchPin);
	begin();
	void LCD_Char(char character);
	void Str(String text);
	void Int(int n);
	void Clear();
	void SetCursor(byte row, byte col);
	
  private:
	byte _dataPin;
	byte _clockPin;
	byte _latchPin;
	byte _cmdval;
    byte _lcdval;
	void SetE();
	void LCD_Init();
	void LCD_Write(byte cmd,byte cmddta);
	void LCDShift(byte lcdval);
};

#endif