#include <SoftwareSerial.h>


//Set uultrasonic sensor
int trigPin=9;
int echoPin=10;

//Set motors
int reverseright=4;  
int forwardright=5;  
int reverseleft=6;      
int forwardleft=7; 
    
//Set bluetooth      
SoftwareSerial BT(10, 11); //TX, RX respetively
String readvoice;

void setup() {
   Serial.begin(9600); 
   pinMode(reverseright, OUTPUT);
   pinMode(forwardright, OUTPUT);
   pinMode(reverseleft, OUTPUT);
   pinMode(forwardleft, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(trigPin, OUTPUT);
}
 
void loop() {
  //set the ultrasonic sensor detection
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/30;
  delay(10);
 
  //Detecting the obstacles and change direction
  if((distance>20))
 {
  digitalWrite(forwardright,HIGH);                               
   digitalWrite(reverseright,LOW);                               
   digitalWrite(reverseleft,LOW);                 
   digitalWrite(forwardleft,HIGH);         
 }
 
  else if(distance<20)  
 {
   digitalWrite(forwardright,HIGH);
   digitalWrite(reverseright,LOW);
   digitalWrite(reverseleft,HIGH);                             
   digitalWrite(forwardleft,LOW);
                                            
 }
while (BT.available()){  //Check if there is an available byte to read
  delay(1000); 
  char c = BT.read(); 
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readvoice.length() > 0) {
    Serial.println(readvoice); 

  if(readvoice == "forward") 
  {
    digitalWrite(reverseright, HIGH);
    digitalWrite (forwardright, HIGH);
    digitalWrite(reverseleft,LOW);
    digitalWrite(forwardleft,LOW);
    delay(1000);
  } 
  
  else if(readvoice == "reverse") 
  {
    digitalWrite(reverseright, LOW);
    digitalWrite(forwardright, LOW);
    digitalWrite(reverseleft, HIGH);
    digitalWrite(forwardleft,HIGH);
    delay(1000);
  }
  
  else if (readvoice == "right")
  {
    digitalWrite (reverseright,HIGH);
    digitalWrite (forwardright,LOW);
    digitalWrite (reverseleft,LOW);
    digitalWrite (forwardleft,LOW);
    delay (1000);
    
  }
  
 else if ( readvoice == "left")
 {
   digitalWrite (reverseright, LOW);
   digitalWrite (forwardright, HIGH);
   digitalWrite (reverseleft, LOW);
   digitalWrite (forwardleft, LOW);
   delay (1000);
 }
 
 else if (readvoice == "stop")
 {
   digitalWrite (reverseright, LOW);
   digitalWrite (forwardright, LOW);
   digitalWrite (reverseleft, LOW);
   digitalWrite (forwardleft, LOW);
   delay (1000);
 }
 
readvoice="";
}

}
