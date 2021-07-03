#include <Stepper_28BYJ.h> //не из коробки
#include <Servo.h>  //из коробки
#include <Ultrasonic.h> //из коробки
#include <SoftwareSerial.h>
#define pwm 9
SoftwareSerial mySerial = SoftwareSerial(10, 11);
Ultrasonic ult(39, 38);
Stepper_28BYJ mySetep (4078, 22,24,26,28);
Servo myServ;
Servo myServ1;
Servo myServ2;
Servo myServ3;
int laser = 50;
int Rmot = 8;
int Lmot = 7;
int mean = 90;
int pezo = 52;
int led = 53;
char val;
bool c1, c2, c3, p1, l1, la;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  myServ.attach(35);
  myServ1.attach(34);
  myServ2.attach(33);
  myServ3.attach(32);
  pinMode(pezo, OUTPUT);
  pinMode(pezo, OUTPUT);
  pinMode(Rmot, OUTPUT);
  pinMode(Lmot, OUTPUT);
  pinMode(laser, OUTPUT);
  /*----------------------------------------*/
  myServ1.write(0);
  myServ2.write(0);
  myServ3.write(0);
  
}

void loop() {
  myServ.write(mean);
  if (mySerial.available())
  {
    val = char(mySerial.read());
    mySerial.print(val);
  }
  switch (val)
  {
    //------servo 360----------------------------------------------------
    case ('q'):
      mean = 180;
      mySerial.print("S-180");
      break;
    case ('w'):
      mean = 0;
      mySerial.print("S-0");
      break;
    case ('e'):
      mean = 90;
      mySerial.print("S-90");
      break;
     // -----------stepper------------------------------------------------
    case ('a'):
      mySetep.step(64);
      mySerial.print("Step");
      break;
    case ('b'):
      mySetep.step(-64);
      mySerial.print("Step");
      break;
    //------------seros---------------------------------------------------
    case ('s'):
      if (c2 == 0){
       myServ2.write(180);
       c2 = 1;
       mySerial.print(c2);
      }
      else{
       myServ2.write(0);
       c2 = 0;
       mySerial.print(c2);
      }
      
      break;
    case ('o'):
      if (c3 == 0){
        myServ3.write(180);
        c3 = 1;
        mySerial.print(c3);
        }
     else{
       myServ3.write(0);
       c3 = 0;
       mySerial.print(c3);
      }
       break;
    case ('p'):
      if (c1 == 0){
        myServ1.write(180);
        c1 = 1;
        mySerial.print(c1);
      }
      else{
        myServ1.write(0);
        c1 = 0;
        mySerial.print(c3);
      }      
      break;
    //------------------ultra sonic---------------------------------------------
    case ('u'):
      mySerial.print(ult.distanceRead());
      break;
    //-----------------piezo----------------------------------------------------
    case ('i'):
      if (p1 == 0){
        digitalWrite(pezo, LOW);
        p1 = 1;
        mySerial.print(p1);
      }
      else{
        digitalWrite(pezo, HIGH);
        p1 = 0;
        mySerial.print(p1);
      }      
      break;
    //-----------------leds----------------------------------------------------
    case ('l'):
      if (l1 == 0){
        digitalWrite(led, LOW);
        l1 = 1;
        mySerial.print(l1);
      }
      else{
        digitalWrite(led, HIGH);
        l1 = 0;
        mySerial.print(l1);
      }      
      break;
   //---------------motor functions--------------------------------------------
      case ('g'):  //-----------mx-speed right
        digitalWrite(Rmot, HIGH);
        digitalWrite(Lmot, LOW);
        analogWrite(pwm, 255);
        break;  
      case ('h'):  //-----------mx-speed left
        digitalWrite(Rmot, LOW);
        digitalWrite(Lmot, HIGH);
        analogWrite(pwm, 255);
        break;   
      case ('t'):  //-----------stop
        digitalWrite(Rmot, LOW);
        digitalWrite(Lmot, LOW);
        analogWrite(pwm, 0);
        break;     
//---------------Laser functions--------------------------------------------    
      case ('j'):
      if (la == 0){
        digitalWrite(laser, LOW);
        la = 1;
        mySerial.print(la);
      }
      else{
        digitalWrite(laser, HIGH);
        la = 0;
        mySerial.print(la);
      }      
      break;
  }
}
