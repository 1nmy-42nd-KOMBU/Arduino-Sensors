#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); // RX, TX
// this sample code provided by www.programmingboss.com
void setup() {
  Serial.begin(9600);
  mySerial.begin(57600);
  Serial.println("Hello Boss");
}
void loop() {
  mySerial.write(32);
  Serial.flush();

  bool iftimeout = true;
  unsigned long start_time = millis();
  while (iftimeout){
    if (mySerial.available() > 0){iftimeout = false;}
    if (millis() - start_time > 10){
      Serial.println("timeout");
      mySerial.write(32);
      Serial.flush();
      start_time = millis();
      continue;
    }
    Serial.println("w");
  }
  char byte_count = 0;
  int8_t list_arduino[9] = {0,0,0,0,0,0,0,0,0};
  Serial.println(mySerial.available());
  while (mySerial.available() > 0) {
    list_arduino[byte_count] = mySerial.read();
    byte_count += 1;
  }
  Serial.println((int8_t)byte_count);
  if (list_arduino[0] == 64){
    Serial.print("t;"); // tof----------------------------
//    if (list_arduino[2] < 0){
//      Serial.println(list_arduino[1]*256+list_arduino[2]+256);
//    } else {
//      Serial.println(list_arduino[1]*256+list_arduino[2]);
//    }
//
//    Serial.print("Gy; "); // Gyro--------------------------
//    int16_t x_tmp = list_arduino[3]*256+list_arduino[4];
//    if (x_tmp <= -1 && x_tmp >= -128){
//      Serial.print(x_tmp+256);
//    } else {Serial.print(x_tmp);}
//    Serial.print(",");
//    Serial.println(list_arduino[5]);
//
//    Serial.print("UL; ");
//    Serial.println((list_arduino[6]+127)*2);
//    Serial.print("UR; ");
//    Serial.println((list_arduino[7]+127)*2);
  } else {Serial.print("e");}
  //delay(1500);
}
