
//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 3000;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already



/* TM1637_4_Digit_Display_Basics.ino
The purpose of this sketch is to provide the basic
structure for using the TM1637 based 4-Digit Displays
like the Grove 4 digit display or other equivalents
available through the likes of www.dx.com. 

This makes use of the TM1637Display library developed by avishorp.
https://github.com/avishorp/TM1637

This has been developed to run on any Arduino.

Pin assignments are:
CLK - D9
DIO - D8
5V or 3.3V supply to Display
GND to Display

The operation is very simple.  The sketch initialises the display
and then steps through the loop incrementing the value of a
variable which is then displayed on the 4-Digit display.
Essentially it is the most basic function you would want from
such a display.  If you want more sophisticated functionality
then use the example that ships with the library.

*/
#include <TM1637Display.h>

const int CLK = 9; //Set the CLK pin connection to the display
const int DIO = 8; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

boolean SC_flag = 0; //for single click event flag; 0 - normal stage; 1 - configure stage
boolean DC_flag = 0; //for double click event flag; 0 - operation stage; 1 - configure stage
/* digit1 = last default value;
digit2 = last default value;
digit3 = last default value;
digit4 = last default value; */

cursor_pos = 3; //position 3 is no of times we want to run
/* pos1 is for no motor pump running time (in minutes- 1 to 9 minutes max)
    pos2 is for time interval between those motor pump running (in minutes 1-9 minutes max)
    pos3 & pos4 is for how many times we want motor pump to run - 1 to 99 times*/

int digit0, digit1, digit2;
//From bildr article: https://bildr.org/2012/08/rotary-encoder-arduino/

//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;
int encoderSwitchPin = 4; //push button switch

// I don't know whether I need them all
volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
display.setBrightness(0x0a);  //set the diplay to maximum brightness    

Serial.begin (9600);

pinMode(encoderPin1, INPUT);
pinMode(encoderPin2, INPUT);

pinMode(encoderSwitchPin, INPUT);

digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

digitalWrite(encoderSwitchPin, HIGH); //turn pullup resistor on

//call updateEncoder() when any high/low changed seen
//on interrupt 0 (pin 2), or interrupt 1 (pin 3)
attachInterrupt(0, updateEncoder, CHANGE);
attachInterrupt(1, updateEncoder, CHANGE);

}
loop(){
 // Checking Single click or double click
   int b = checkButton();
   if (b==1) clickEvent();
   if (b==2) doubleClickEvent();
    
   if (DC_flag==1){
       if (cursor_pos==3){
           //blink digit3
           display.showNumberDec(digit2,false,2,2); //Show two digit number; position 2; no leading 0
           delay(500);
           display.showNumberDec(,false,2,2); //Show two digit number; position 2; no leading 0
           delay(500);
           if (SC_flag==1) chg_digit0=0;
            }
           else if (cursor_pos == 2)
           // blink digit2
           display.showNumberDec(digit1,false,1,1); //Show two digit number; position 2; no leading 0
           delay(500);
           display.showNumberDec(,false,1,1); //Show two digit number; position 2; no leading 0
           delay(500);
            if (SC_flag==1) chg_digit1=1;
            } 
           else 
           // blink digit1
           display.showNumberDec(digit0,false,1,0); //Show two digit number; position 2; no leading 0
           delay(500);
           display.showNumberDec(,false,1,0); //Show two digit number; position 2; no leading 0
           delay(500);
            if (SC_flag==1) chg_digit2==;
            }
           }
       
//display.showNumberDec(10,false,2,0);


}
int checkButton() {    
   int event = 0;
   buttonVal = digitalRead(buttonPin);
   // Button pressed down
   if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;
       longHoldEventPast = false;
       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button released
   else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
   {        
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 2;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 1;
       DCwaiting = false;
   }
}
clickEvent(){
    SC_flag=!SC_flag;
}
doubleClickEvent(){
    DC_flag1=!DC_flag;

}
    
    void updateEncoder(){
int MSB = digitalRead(encoderPin1); //MSB = most significant bit
int LSB = digitalRead(encoderPin2); //LSB = least significant bit

int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number 
int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value 
        if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++; 
        if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --; 
        lastEncoded = encoded; //store this value for next time }
