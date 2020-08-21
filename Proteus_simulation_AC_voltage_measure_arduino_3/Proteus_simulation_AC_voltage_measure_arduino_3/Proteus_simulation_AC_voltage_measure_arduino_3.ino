#include <LiquidCrystal.h> //library for LCD
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 
//Measuring Current Using ACS712
 float Power=0;
 float Energy=0;
const int analogchannel = 0; //Connect current sensor with A0 of Arduino
int sensitivity = 100; // use 100 for 20A Module and 66 for 30A Module
float adcvalue= 0;
int offsetvoltage = 2500; 
double Voltage = 0; //voltage measuring
double Irms = 0;// Current measuring
// get maximum reading value

//Time calculations
unsigned long CurrentTime;
unsigned long StartTime;
unsigned long ElapsedTime;
void setup() {
 //baud rate
 Serial.begin(9600);//baud rate at which arduino communicates with Laptop/PC
 // set up the LCD's number of columns and rows:
 lcd.begin(20, 4); //LCD order
 // Print a message to the LCD.
 lcd.setCursor(1,1);//Setting cursor on LCD
  delay(100);

}
//Function to measure voltage
uint16_t get_max() {
  uint16_t max_v = 0;
  for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(3);  // read from analog channel 3 (A3)
    if(max_v < r) max_v = r;
    delayMicroseconds(200);
  }
  return max_v;
} 
void loop() //method to run the source code repeatedly
{ 

StartTime=millis();
//Introduction
lcd.display();
lcd.setCursor(0,0);//Setting cursor on LCD
lcd.print("SMART ENERGY METER");
//Voltage calculation
char buf[10];
uint32_t Vrms = get_max();
Vrms = Vrms * 1100/1023;
  // calculate the RMS value ( = peak/√2 )
Vrms /= sqrt(2);
Vrms=Vrms*57.5;//Constant
sprintf(buf, "%03u V", Vrms);

lcd.setCursor(0, 1);
lcd.print("V=");//Diplays Vrms
lcd.print(buf);//Display voltage

//Current calculation
unsigned int temp=0;
float maxpoint = 0;
int i=0;

 for(i=0;i<500;i++)
 {
 if(temp = analogRead(analogchannel),temp>maxpoint)
 {
 maxpoint = temp;
 }
 }
 adcvalue = maxpoint; 
 Voltage = (adcvalue / 1024.0) * 5000; // Gets you mV
 Irms = ((Voltage - offsetvoltage) / sensitivity);
 Irms = ( Irms ) / ( sqrt(2) );

//Power calculations
Power=Vrms*Irms;
//Energy calculations

Energy=(Power*StartTime)/(1000);
Energy=Energy/3600;
//Display values
 lcd.setCursor(8,1);
 lcd.print("I=");//Display Irms
 lcd.print(Irms,3);
 lcd.print("A"); //unit for the current to be measured

 lcd.setCursor(0,2);
 lcd.print("P=");//Display Prms
 lcd.print(Power,3);
 lcd.print("W"); //unit for the power to be measured
 
 lcd.setCursor(0,3);
 lcd.print("E=");//Display Energy
 lcd.print(Energy);
 lcd.print("Kwh"); //unit for the Energy to be measured
 delay(1000); //delay of 2.5 sec
}
