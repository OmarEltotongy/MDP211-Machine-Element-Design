// Include the Arduino Stepper Library
#include <LiquidCrystal.h>
// Number of steps per output rotation

const int SPR = 200;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Potentiometer A5 
#define RSwitch 13
#define PB 7
const int stepPin = 8; 
const int dirPin = 9; 
const int enPin = 10;
const int RS=1140; // max up steps
float theta;
float v;
int CurrentS;
  int NewS;
  int C=0;
void setup()
{

  // Print a message to the LCD. 
  Serial.begin(9600);
    lcd.begin(16, 2);
  pinMode(PB, INPUT_PULLUP);
   pinMode(RSwitch, INPUT_PULLUP);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW); 
  
}
void loop()
{
     int BEGIN=digitalRead(PB);
  int Switch=digitalRead(RSwitch);
  if(Switch==0 && BEGIN==HIGH && C==0 )
  {
    lcd.clear();
    lcd.print("PITCH CONTROL");

  }
     BEGIN=digitalRead(PB);
   while(BEGIN==HIGH && C==0)
   {
     
    Serial.println("HIGH");
   DOWN(RS);
   BEGIN=digitalRead(PB);
   CurrentS=0;
   if(BEGIN==LOW)
   {
    lcd.clear();
   }
   }
   delay(20);
  Serial.println("LOW");
 
  
       float sensorValue = analogRead(A5);
    float volt = 2.5*(sensorValue/1023);
    float angle = 36*volt;
    NewS=RS*angle/90;
    Serial.println(NewS);
    
  delay(500);
    
 // Serial.println(volt);
  lcd.print("Voltage =");
  lcd.print(volt);
  // lcd.println("                 "); 
  lcd.setCursor(0, 0);
  lcd.print("Angle ="); //angle
  lcd.print(angle); // keep calculation inside print
  // lcd.println("                 "); 
  lcd.setCursor(0, 1);
   Switch=digitalRead(RSwitch);
  if (Switch==1)
  {
    int S=NewS-CurrentS;
    Serial.println(S);
    if(S>0)
    {
      UP(S);

    }
    if(S<0)
    {
      DOWN(-S);
    }
     C=1;
     CurrentS=NewS;
    
  }
  delay(20);
 
 

}

void DOWN(int z)
{
  Serial.println("DOWN");
   digitalWrite(dirPin,LOW); //Changes the direction of rotation
  for(int x = 0; x < z; x++) {
    if(digitalRead(PB)==LOW)
    {
      break;
    }
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }
  delay(500); 
}

void UP(int y)
{
  Serial.println("UP");
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  for(int x = 0; x < y; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000); 
  }
  delay(500);
}
