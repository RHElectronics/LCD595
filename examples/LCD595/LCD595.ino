//LCD595 RH Electronics, June 2018

//595 is set to LSB first
//D4 through D7 connected to Q7 through Q4
//E on Q3
//RS on Q4

//Available Commands
//Clear() //SetCursor  //Str (for strings) //Int (For integer/bytes)

//Declare the library below - with the pins required in order stated

#include <LCD595.h>
LCD595 LCD(5,6,7);      //Data Pin, Clock Pin, Latch Pin



void setup() {

  // put your setup code here, to run once:
  LCD.begin();    //Always start with the begin() command
  
  LCD.Clear();
  LCD.SetCursor(0,0);
  LCD.Str("595 LCD");
}

void loop() {
  // put your main code here, to run repeatedly:

}
