/* Настройки для приложения Serial Bluetooth Terminal:
 * Sittings > Receive > Newline (CR+LF) 
 * _________> Send > Newline (NUL)
 */

#define tx 2
#define rx 3
#include <SoftwareSerial.h>;
char m, info;

SoftwareSerial mySerial = SoftwareSerial(rx, tx);
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (mySerial.available()){ 
      //info = int(mySerial.parseInt());
      info = mySerial.read();
      //m = mySerial.read();
      Serial.println(info);
      //mySerial.println(info);
  }
}

void action(int info){
  info = 0;
}
