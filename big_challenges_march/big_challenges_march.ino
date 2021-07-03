#include <SoftwareSerial.h>
#include <Servo.h>
#define rx 3
#define tx 2
#define pwm 6
#define r1 1
#define r2 8
#define r3 10
#define r4 12
#define l1 7
#define l2 9
#define l3 11
#define l4 13
int pwm_speed = 255;
int in;
char info;
bool count = 0;

SoftwareSerial mySerial = SoftwareSerial(rx, tx);
Servo myservo1;
Servo myservo2;

void setup() {
  mySerial.begin(9600);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  myservo1.attach(4);
  myservo2.attach(5);
  myservo1.write(0);
  myservo2.write(0);
}

void loop() {
  if(mySerial.available()){
    info = char(mySerial.read());
    switch (info){
     case 'u':
       up();
       break;
     case 'd':
       down();
       break;
     case 't':
       turn ();
       break;
     case 's':
       stopper();
       break;
  }
 }
}

void up (){
  analogWrite(pwm, pwm_speed);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);
  mySerial.print(pwm_speed);
}

void down (){
  analogWrite(pwm, pwm_speed);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);
  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, HIGH); 
  mySerial.print(pwm_speed); 
}

void stopper (){
  analogWrite(pwm, 0);
  mySerial.print(pwm_speed); 
}

void turn (){
  if (count == 0){
    myservo1.write(90);
    myservo2.write(90); 
    count = 1;
  }
  else {
    myservo1.write(0);
    myservo2.write(0); 
    count = 0;   
  }
}
