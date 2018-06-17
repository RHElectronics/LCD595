/*
  RH Electronics 595 LCD Library
  June 2018
*/

#include "Arduino.h"
#include "LCD595.h"

//Declare
LCD595::LCD595(byte dataPin, byte clockPin, byte latchPin){
  _dataPin = dataPin;
  _clockPin = clockPin;
  _latchPin = latchPin;
}

//Begin
LCD595::begin(){
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  
  delay(50);
  LCD_Init();
}

//Write to LCD via shift regsiter
void LCD595::LCD_Write(byte cmd,byte cmddta){
//Value of RS
  if(cmddta == 1){_lcdval = (_lcdval & ~B00100000) | 32; }
  else {_lcdval = (_lcdval & ~B00100000);}

  LCDShift(_lcdval);
  
  //Write MSB
  _cmdval = (cmd & 240) >>4;
  _lcdval = (_lcdval & ~B00001111) | _cmdval;

  LCDShift(_lcdval);
  SetE();

  //Write LSB
  _cmdval = cmd & 15;
  _lcdval = (_lcdval & ~B00001111) | _cmdval;
  
  LCDShift(_lcdval);
  SetE();
}

//Pulse the E line
void LCD595::SetE(){
  delay(0.5);
  _lcdval = (_lcdval & ~B00010000) | 16;    //Add bit
  LCDShift(_lcdval);
  delay(0.5);
  _lcdval = (_lcdval & ~B00010000);         //Remove bit
  LCDShift(_lcdval);
  delay(1);
}

//LCD Shift Out
void LCD595::LCDShift(byte _lcdval){
  digitalWrite(_latchPin,LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, _lcdval);
  digitalWrite(_latchPin,HIGH);
}

//Write Character
void LCD595::LCD_Char(char character){
  LCD_Write(character,1);
}

//Write String
void LCD595::Str(String text){
 char *chrarray = new char[text.length()];
 strcpy(chrarray, text.c_str());
 while(*chrarray) LCD_Char (*chrarray++);
}

//Write Integer
void LCD595::Int(int n){
  char c[10];
  sprintf(c, "%d", n);
  for (int i=0;c[i] > 0 ;i++) LCD_Char(c[i]); 
 }

//Clear LCD
void LCD595::Clear(){
  LCD_Write(0x01,0);
}

//Set Cursor
void LCD595::SetCursor(byte row, byte col){
   if (col == 0)LCD_Write((row | 0x80),0);
   if (col == 1)LCD_Write((row | 0x80)+ 0x40,0);
   if (col == 2)LCD_Write((row | 0x80)+ 0x10,0);
   if (col == 3)LCD_Write((row | 0x80)+ 0x50,0);
   delay(0.5);
}

//Initialize
void LCD595::LCD_Init(){
  LCD_Write(0x33,0);
  delay(0.5);
  LCD_Write(0x32,0);
  delay(0.5);
  LCD_Write(0x28,0);
  delay(0.5);
  LCD_Write(0x0C,0);
  delay(0.5);
  LCD_Write(0x06,0);
  delay(0.5);
  LCD_Write(0x01,0);
  delay(0.5);
}