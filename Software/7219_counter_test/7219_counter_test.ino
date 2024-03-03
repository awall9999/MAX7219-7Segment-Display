/*
 Test Program for the Max7219 8x7 segment dislay by Alain`s Projects
 (c) www.alainsprojects.com
 Ver 1.0
 */


int latchPin = 2;// CS or Load pin to the MAX7219
int clockPin = 3;// Clock pin to the MAX7219
int dataPin = 4;// Fata pin to the MAX7219

byte POS[8]={4,3,2,1,8,7,6,5}; //order in which the individual segments are connected to the MAX7219
byte Number[11]={126,48,109,121,51,91,31,112,127,115,128}; //Segment code 0,1,2,3,4,5,6,7,8,9,:
byte NUMBER[8]={0,0,0,0,0,0,0,0};
long int SegmentValue = 0;
 
byte Value = 0;
byte Address = 0;

void shift(byte MaxAddress, byte MaxData) // send Address and Data to MAX7219
{
  digitalWrite(latchPin, LOW); //Enable Data Load to Max7219
  shiftOut(dataPin, clockPin, MSBFIRST, MaxAddress); //Send AdressByte
  shiftOut(dataPin, clockPin, MSBFIRST, MaxData); //Send DataByte
  digitalWrite(latchPin, HIGH); //Disable Data Load to Max7219
}


void InitMax() //Setup of MAX7219 chip
{
  shift(0x0f, 0x00); //test mode off
  shift(0x0b, 0x07); //display digits 0 thru 7
  shift(0x0c, 0x01); //normal operation
  shift(0x0a, 0x02); //brightness
  shift(0x09, 0x00); //No decode
}
void Clear() // clear display
{
 InitMax();
 for (int i = 0; i <= 7; i++) {
 Address=(POS[i]);
 Value=0;
 shift(Address,Value);
 
 }
}

void calc(){
long int c=10;

for (int i = 0; i <= 7; i++) {
NUMBER[i]= ((SegmentValue % c)/(c/10)); 

c=c*10;
}
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  InitMax(); //init MAX2719 chip
  Clear();
  
}

void loop() {
 calc();
 InitMax();
 for (int i = 0; i <= 7; i++) {
 Address=(POS[i]); //Selection of the Segment. 0=Right Digit to 7=Left Digit
 Value=Number[NUMBER[i]]; //Display Value 0-9 and : or . 
 shift(Address,Value); //Send Data to Display
 
 }
 SegmentValue++; //Increment counter
 if (SegmentValue>99999999) SegmentValue=0;
 }   
