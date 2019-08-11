boolean flag = 0; // 0 - configure stage; 1 - operation stage
/* digit1 = last default value;
digit2 = last default value;
digit3 = last default value;
digit4 = last default value; */

cursor_pos = 4; /position 4 is no of times we want to run/
/* pos1 is for no motor pump running time (in minutes- 1 to 9 minutes max)
    pos2 is for time interval between those motor pump running (in minutes 1-9 minutes max)
    pos3 & pos4 is for how many times we want motor pump to run - 1 to 99 times*/
    
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

