#include<Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal LCD(7, 6, 5, 3, 1, 0);
const int pingPin = 8;
int servoPin = 9;
float MinTemp = 20, MaxTemp = 25;

Servo servo1;

void setup() {
  // initialize serial communication:
  //Serial.begin(9600);
  LCD.begin(16,2);
  servo1.attach(servoPin);
  pinMode(2,INPUT);
  pinMode(4,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A0,INPUT);
  
  
  digitalWrite(2,LOW);
  digitalWrite(11,HIGH);
  LCD.clear();

  LCD.print("temp in(degreeC):");
  LCD.setCursor(2,1);
  LCD.print(MinTemp); LCD.print("-");LCD.print(MaxTemp);

  delay(2000);
  
}

void loop() {
  
  long duration, inches, cm;
  
  //temp with fan
  float value=analogRead(A0) * 5.0 / 1023;
  float temperature=100*value-50;
  

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  digitalWrite(6,HIGH);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();
  //delay(100);
  
  servo1.write(0);
  
  if(cm < 40)
  {
    LCD.clear();
    LCD.print("Opening Door.");
    servo1.write(90);
    delay(2000);
  }
  else
  {
    servo1.write(0);
  }
  
  // PIR with LED starts
  int pir = digitalRead(2);
  
  if(pir == HIGH)
  {	
    LCD.clear();
    LCD.print("Turning on lights");
    digitalWrite(4,HIGH);
    delay(1000);
  }
  else if(pir == LOW)
  {
    digitalWrite(4,LOW);
  }
  LCD.clear();
    LCD.print("Sensor reading:");
    LCD.setCursor(2,1);
    LCD.print(temperature); LCD.print(" C");
   
    delay(200);
  
  if(temperature > MaxTemp){
      LCD.clear();
      LCD.print("Its too HOT!");
     
      LCD.setCursor(0, 1);LCD.print("Turn on FAN!");
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      delay(2000);
     
      LCD.clear();
      LCD.print("Now temp is OK!");
      LCD.setCursor(0, 1);
      LCD.print("FAN TURNS OFF!");
     
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      delay(2000);
      }else if(temperature < MinTemp){
      LCD.clear();
    
    //If The temperature is less than minimmun
      LCD.print("Its Cold NOW!");
      LCD.clear();
      delay(500);
      LCD.print("Heater is ON!");

    
     //Turning the heater(LED) ON automatically,  
    
      digitalWrite(10, HIGH);
    
      delay(300);
    
      LCD.clear();
      LCD.print("Now temp is OK!");
      delay(500);
      LCD.clear();
      LCD.setCursor(0, 1);
      LCD.print("Turn off HEATER!");
    
      delay(1000);
    
      digitalWrite(10, LOW);
      LCD.clear();
      }
  
  else if(temperature > MinTemp && temperature < MaxTemp)
  {/* temperature is normal and saving energy*/
      LCD.clear();
      LCD.print("Temp is NORMAL!");LCD.setCursor(2,1);
      delay(500);
      LCD.clear();
      LCD.print("Saving Energy!");
    
      delay(1000);
      LCD.clear();
   }  
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

