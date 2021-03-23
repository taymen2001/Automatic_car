#include <SoftwareSerial.h>
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo
int Echo = A0;  
int Trig = A1; 
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
const int ENA = 8;
const int ENB = 13;
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;
 
unsigned char carSpeed = 255;
bool state = LOW;
char getstr;

void forward(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");
  delay(150);
  getstr = 's';
}
void back(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
  delay(150);
  getstr = 's';
}
void right(){ 
  digitalWrite(ENA,carSpeed);
  digitalWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("Forward");
  delay(150);
  getstr = 's';
}
void left(){
  digitalWrite(ENA,carSpeed);
  digitalWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Back");
  delay(150);
  getstr = 's';
}
void forwardauto(){
  analogWrite(ENA,150);
  analogWrite(ENB,150);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");
}

void backauto(){
  analogWrite(ENA,150);
  analogWrite(ENB,150);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
}
void rightauto(){ 
  digitalWrite(ENA,150);
  digitalWrite(ENB,150);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("Forward");
}
 
void leftauto(){
  digitalWrite(ENA,150);
  digitalWrite(ENB,150);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Back");
}
 
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  
 
void stop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
}
 
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() { 
   myservo.attach(A4);
  Serial.begin(9600);
  mySerial.begin(38200);
  myservo.write(110); 
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);  
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  stop();
}
 
void loop() { 
  if (mySerial.available()> 0){
  getstr = mySerial.read();
  Serial.println(getstr);
  }
  switch(getstr){
    case 'f': forward(); break;
    case 'b': back();   break;
    case 'l': left();   break;
    case 'r': right();  break;
    case 's': stop();   break;
    case 'a': 
    myservo.write(110);  //setservo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();
 
    if(middleDistance <= 50) {     
      stop();
      delay(500);                         
      myservo.write(180);          
      delay(1000);      
      rightDistance = Distance_test();
      delay(500);
      myservo.write(110);              
      delay(1000);                                                  
      myservo.write(10);              
      delay(1000); 
      leftDistance = Distance_test();
      delay(500);
      myservo.write(110);              
      delay(1000);
      if(rightDistance > leftDistance) {
        rightauto();
        delay(100);
      }
      else if(rightDistance < leftDistance) {
        leftauto();
        delay(100);
      }
      else if((rightDistance <= 30) || (leftDistance <= 30)) {
        backauto();
        delay(100);
      }
      else {
        forwardauto();
      }
    }  
    else {
        forwardauto();
    }                     
    break;
    default:  break;
  }
}
