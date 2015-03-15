#define TrigPin 8
#define Echo 9
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

long Time, Distance;


void setup(){
  
// I/O DECLARATIONS
pinMode(TrigPin, OUTPUT);
pinMode(Echo, INPUT);
digitalWrite(TrigPin, LOW); //Initialize trigger as low 
    
Serial.begin(9600);    //Serial Communication for troubleshooting
}

void loop(){
  
  // Send signal to Trig Pin
  digitalWrite(TrigPin, HIGH); //Writes Trig Pin HIGH
  delayMicroseconds(10); //HC-SR04 Needs a 10uS pulse sent to trigger
  digitalWrite(TrigPin, LOW);  //Sends Trig Pin Low
  
  // variables to read sensor feedback

  Time = pulseIn(Echo, HIGH);
  Distance = (Time / 148);    //Distance in inches, eqn from datasheet

  lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(Distance);
  delay(100);
  lcd.clear();
  delay(10);
  }

