#include "Keypad.h"
#include "Adafruit_NeoPixel.h"
#define PIN 13                  // пин DI
#define NUM_LEDS 50             // число диодов
#define PIN_POT A0
const byte ROWS = 4;            //four rows
const byte COLS = 4;            //three columns
char keys[ROWS][COLS] = {
  {'0',  '1', '2', '3'},
  {'4',  '5', '6', '7'},
  {'8',  '9', 'A', 'B'},
  {'C',  'D', 'E', 'F'}
};
byte rowPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3,2,8,9}; //connect to the column pinouts of the keypad

bool STOP = 0; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  pinMode(PIN_POT, INPUT);
  
  strip.begin();
  strip.setBrightness(50);    // яркость, от 0 до 255
  strip.clear();                          
  strip.show(); 

//  BEGINING
//  for (int i = 0; i < NUM_LEDS; i++ ) {   // от 0 до первой трети
//    strip.setPixelColor(i, strip.Color(RED, GREEN, BLUE));     // залить красным
//    strip.show();                         // отправить на ленту
//    delay(100);
//  }
}

void loop() {
  int bright = analogRead(PIN_POT);
  strip.setBrightness(bright/4);   // яркость, от 0 до 255
  strip.show();

  char key = keypad.getKey();
  if (key != NO_KEY){
    switch (key) {
      case '0':
        cRED(NUM_LEDS);
        break;  
      case '1':
        cGREEN(NUM_LEDS);
        break;
      case '2':
        cBLUE(NUM_LEDS);
        break;
      case '3':
        cALL(NUM_LEDS);
        break;
      case '4':
        cPURPLE(NUM_LEDS);
        break;
      case '5':
        cLIME(NUM_LEDS);
        break;
      case '6':
        cOCEAN(NUM_LEDS);
        break;
      case '7':
        cMY(NUM_LEDS);
        break;
      case '8':
        SNAKE_purple();
        break;
      case '9':
        SNAKE_lime();
        break;
      case 'A':
        SNAKE_ocean();
        break;
      case 'B':
        SNAKE_all();
        break;
      case 'C':
        STATIC_vanila();
        break;
      case 'D':
        STATIC_new();
        break;
      case 'E':
        FLASHER_vanila();
        break;
      case 'F':
        FLASHER_new();
        break;                     
      }
    }
  }

void cRED(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(255, 0, 0));     
        strip.show(); 
  }
}

void cGREEN(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(0, 0, 255));     
        strip.show(); 
  }
}

void cBLUE(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(0, 255, 0));
        strip.show(); 
  }
}

void cALL(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(255, 255, 255));
        strip.show(); 
  }
}

void cPURPLE(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(255, 255, 0));
        strip.show(); 
  }
}

void cLIME(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(255, 0, 255));
        strip.show(); 
  }
}

void cOCEAN(int counter)          
{
  for (int i = 0; i < NUM_LEDS; i++ ) {   
        strip.setPixelColor(i, strip.Color(0, 255, 255));
        strip.show(); 
  }
}

void cMY(int counter)          
{
  for (int i = 0; i < counter; i++ ) {   
        strip.setPixelColor(i, strip.Color(200, 150, 100));
        strip.show(); 
  }
}

void SNAKE_ocean()          
{
  while (STOP == 0) {
    for (int i = 0; i < NUM_LEDS; i++ ) {   
        for (int j = i; j < i + 4; j++ ) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(0, 255, 255));
          strip.setPixelColor(j-3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    for (int i = 49; i > -1; i--) {   
        for (int j = i; j > i - 4; j--) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(0, 255, 255));
          strip.setPixelColor(j+3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    }
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
      strip.setPixelColor(i, 0x000000);     // залить чёрным
      strip.show();                         // отправить на ленту
  }
  STOP = 0;
}

void SNAKE_purple()          
{
  while (STOP == 0) {
    for (int i = 0; i < NUM_LEDS; i++ ) {   
        for (int j = i; j < i + 4; j++ ) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(255, 255, 0));
          strip.setPixelColor(j-3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    for (int i = 49; i > -1; i--) {   
        for (int j = i; j > i - 4; j--) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(255, 255, 0));
          strip.setPixelColor(j+3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    }
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
      strip.setPixelColor(i, 0x000000);     // залить чёрным
      strip.show();                         // отправить на ленту
  }
  STOP = 0;
}

void SNAKE_lime()          
{
  while (STOP == 0) {
    for (int i = 0; i < NUM_LEDS; i++ ) {   
        for (int j = i; j < i + 4; j++ ) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(255, 0, 255));
          strip.setPixelColor(j-3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    for (int i = 49; i > -1; i--) {   
        for (int j = i; j > i - 4; j--) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}   
          strip.setPixelColor(j, strip.Color(255, 0, 255));
          strip.setPixelColor(j+3, 0x000000);
          strip.show();
          delay(102 - speed/10);
        } 
      }
    }
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
      strip.setPixelColor(i, 0x000000);     // залить чёрным
      strip.show();                         // отправить на ленту
  }
  STOP = 0;
}

void SNAKE_all()          
{
  while (STOP == 0) {
    int G, B, R;
    for (int i = 0; i < NUM_LEDS; i++ ) {   
        for (int j = i; j < i + 3; j++ ) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}  
          switch (j-i) {
            case 0:
              G=0;
              B=255;
              R=255; 
              break;  
            case 1:
              G=255;
              B=0;
              R=255 ;
              break; 
            case 2:
              G=255;
              B=255;
              R=0 ;
              break;
            case 3:
              G=255;
              B=255;
              R=255 ;
              break;
            }
          strip.setPixelColor(j, strip.Color(R,B,G));
          strip.setPixelColor(j-3, 0x000000);
          strip.show();
          delay(102 - speed/10);
          } 
        }

      for (int i = 49; i > -1; i--) {
        for (int j = i; j > i - 3; j--) {
          int speed = analogRead(PIN_POT);
          if (speed/10 == 0){STOP = 1; break;}  
          switch (i-j) {
            case 0:
              G=0;
              B=255;
              R=255; 
              break;  
            case 1:
              G=255;
              B=0;
              R=255 ;
              break; 
            case 2:
              G=255;
              B=255;
              R=0 ;
              break;
            case 3:
              G=255;
              B=255;
              R=255 ;
              break;
            }
          strip.setPixelColor(j, strip.Color(R,B,G));
          strip.setPixelColor(j+3, 0x000000);
          strip.show();
          delay(102 - speed/10);
          } 
        }
    }
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
      strip.setPixelColor(i, 0x000000);     // залить чёрным
      strip.show();                         // отправить на ленту
  }
  STOP = 0;
}


void STATIC_vanila()          
{
  int G, B, R;
  for (int i = 0; i < NUM_LEDS; i++) {   
        int bright1 = analogRead(PIN_POT);
        strip.setBrightness(bright1/4);   // яркость, от 0 до 255
        strip.show(); 
        switch (i%3) {
          case 0:
            G=0;
            B=0;
            R=255; 
            break;  
          case 1:
            G=255;
            B=0;
            R=0;
            break; 
          case 2:
            G=0;
            B=255;
            R=0;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      } 
}


void STATIC_new()          
{
  int G, B, R;
  for (int i = 0; i < NUM_LEDS; i++) {   
        int bright1 = analogRead(PIN_POT);
        strip.setBrightness(bright1/4);   // яркость, от 0 до 255
        strip.show(); 
        switch (i%3) {
          case 0:
            G=0;
            B=255;
            R=255; 
            break;  
          case 1:
            G=255;
            B=0;
            R=255 ;
            break; 
          case 2:
            G=255;
            B=255;
            R=0 ;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      } 
}


void FLASHER_vanila()          
{
  int G, B, R;
  int speed1 = analogRead(PIN_POT);
  while (STOP == 0) {
  for (int i = 0; i < NUM_LEDS; i++) { 
        if (speed1/5 == 0){STOP = 1; break;}  
        speed1 = analogRead(PIN_POT);
        strip.show(); 
        Serial.println(speed1/5);
        switch (i%3) {
          case 0:
            G=0;
            B=0;
            R=255; 
            break;  
          case 1:
            G=255;
            B=0;
            R=0;
            break; 
          case 2:
            G=0;
            B=255;
            R=0;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      }
      delay(204 - speed1/5);
  for (int i = 0; i < NUM_LEDS; i++) {   
        if (speed1/5 == 0){STOP = 1; break;}
        speed1 = analogRead(PIN_POT);
        strip.show(); 
        switch (i%3) {
          case 2:
            G=0;
            B=0;
            R=255; 
            break;  
          case 0:
            G=255;
            B=0;
            R=0;
            break; 
          case 1:
            G=0;
            B=255;
            R=0;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      }
    delay(204 - speed1/5);
}
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить чёрным
        strip.show();                         // отправить на ленту
      }
  STOP = 0;
}


void FLASHER_new()          
{
  int G, B, R;
  int speed1 = analogRead(PIN_POT);
  while (STOP == 0) {
  for (int i = 0; i < NUM_LEDS; i++) { 
        if (speed1/5 == 0){STOP = 1; break;}  
        speed1 = analogRead(PIN_POT);
        strip.show(); 
        Serial.println(speed1/5);
        switch (i%3) {
          case 0:
            G=0;
            B=255;
            R=255; 
            break;  
          case 1:
            G=255;
            B=0;
            R=255 ;
            break; 
          case 2:
            G=255;
            B=255;
            R=0 ;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      }
      delay(204 - speed1/5);
  for (int i = 0; i < NUM_LEDS; i++) {   
        if (speed1/5 == 0){STOP = 1; break;}
        speed1 = analogRead(PIN_POT);
        strip.show(); 
        switch (i%3) {
          case 2:
            G=0;
            B=255;
            R=255; 
            break;  
          case 0:
            G=255;
            B=0;
            R=255 ;
            break; 
          case 1:
            G=255;
            B=255;
            R=0 ;
            break;
          }
        strip.setPixelColor(i, strip.Color(R,B,G));
        strip.show();
      }
    delay(204 - speed1/5);
}
    for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить чёрным
        strip.show();                         // отправить на ленту
      }
  STOP = 0;
}
