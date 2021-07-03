#include <math.h>
#include <SoftwareSerial.h>
#define LDR_PIN   A1
#define soil_pin  A2
#define red_led   3
#define green_led 6
#define blue_led  5
#define bazz  2
#define rx 7
#define tx 8

SoftwareSerial mySerial = SoftwareSerial(rx, tx);
float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;
float T,logRt,Tf,Tc;
int info, None;
bool Soil_flag, Flag_light, on_off;
int RGB[] = {250, 0, 50};  

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(bazz, OUTPUT);
  Flag_light = 0;         // для света [0 - автоматическое включение света, 1 - ручное включение света]
  Soil_flag = 0;          // для влажности [0 - автоматическое включение света, 1 - ручное включение света]
  on_off = 0;
}
void loop() 
{
  if (mySerial.available())
  {
    info = mySerial.parseInt();
    None = mySerial.read();
    switch (info)
    {
      case 0:   // включить автономный режим (свет)
        Flag_light = 0;   
        break;
      case 10:  // выключить автономный режим (свет погашен)
        Flag_light = 1;   
        on_off = 0;
        break;
      case 11:  // выключить автономный режим (свет включен)
        Flag_light = 1; 
        on_off = 1;
        break;
      case 20:  // включить автономный режим (пищалка)
        Soil_flag = 0;
        break; 
      case 21:  // выключить автономный режим (пищалка)
        Soil_flag = 1;
        break;  
      case 30:  // температура
        mySerial.print(int(Tc));
        mySerial.println("С");
        break;
      case 40:  // инфрпмация
        if (Flag_light == 1){mySerial.println("light - arm");}
        else{mySerial.println("light - robot");}
        if (Soil_flag == 1){mySerial.println("soil - arm");}
        else{mySerial.println("soil - robot");}
        break;

    }
  }

  if (Flag_light == 0 && analogRead(LDR_PIN) < 30)
  {
    on_off = 1;
    light(RGB, on_off);
  }
  if (Flag_light == 0 && analogRead(LDR_PIN) >= 30)
  {
    on_off = 0;
    light(RGB, on_off);
  }
  light(RGB, on_off);
  //myPrint(1000);
  Thermistor(analogRead(0));
  soil_func(Soil_flag);
}

float Thermistor(int Vo)  // функция для расчета значения температуры
{ 
 logRt = log(10000.0*((1024.0/Vo-1))); 
 T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));   // рассчитываем значение температуры в кельвинах по формуле Стейнхарта-Харта
 Tc = T - 273.15;                                   // переводим температуру из кельвинов в градусы
}

void soil_func(bool Soil_flag)          // функция для коннекта пищалки и датчика влажности
{
  if (int(analogRead(soil_pin)) >= 900 && Soil_flag == 0)
    {
      digitalWrite(bazz, LOW);
    }
  else{
      digitalWrite(bazz, HIGH);
  }
}

void light (int *myArray, bool flag)   // функция для работы со светом [массив с RGB настройками, флаг для включения\выключения]
{
  if (flag == 0){
    analogWrite(red_led, 0);
    analogWrite(green_led, 0);
    analogWrite(blue_led, 0);
  }
  else{
    analogWrite(red_led, myArray[2]);
    analogWrite(green_led, myArray[1]);
    analogWrite(blue_led, myArray[0]);
  }
}

void myPrint(int del)                //функция для отправки данных в Serial компьютера 
{
  Serial.print(int(analogRead(LDR_PIN)));
  Serial.println(" - Light");
  Serial.print(analogRead(soil_pin));
  Serial.println(" - soil");
  Serial.print(Tc);
  Serial.println(" - C");
  delay(del);
}
