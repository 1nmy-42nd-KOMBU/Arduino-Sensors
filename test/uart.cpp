#include <SoftwareSerial.h>
#include<Wire.h>
SoftwareSerial mySerial(4, 5); // RX, TX
// this sample code provided by www.programmingboss.com
void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
}

void loop() {
  Serial.println("send to esp32");
  mySerial.write(32);

  bool iftimeout = true;
  unsigned long start_time = millis();
  while (iftimeout){
    if (mySerial.available() > 0){iftimeout = false;}
    if (millis() - start_time > 10){ // timeout
      Serial.println("timeout");
      break;  
    }
  }
  char byte_count = 0;
  int8_t list_arduino[9] = {0,0,0,0,0,0,0,0,0};
  int8_t left_byte = mySerial.available();
  Serial.println(left_byte);

  while (mySerial.available() > 0) {
    list_arduino[byte_count] = mySerial.read();
    byte_count += 1;
  }
  if (left_byte == 9){}else{
    Serial.println("break");
    break;
  } // chack if there are 9byte

  if (list_arduino[0] == 64){
    Serial.print("tof; "); // tof----------------------------
    if (list_arduino[2] < 0){
      Serial.println(list_arduino[1]*256+list_arduino[2]+256);
    } else {
      Serial.println(list_arduino[1]*256+list_arduino[2]);
    }

    Serial.print("Gyro; "); // Gyro--------------------------
    int16_t x_tmp = list_arduino[3]*256+list_arduino[4];
    if (x_tmp <= -1 && x_tmp >= -128){
      Serial.print(x_tmp+256);
    } else {Serial.print(x_tmp);}
    Serial.print(",");
    Serial.println(list_arduino[5]);

    Serial.print("ultrasonic left; ");
    Serial.println((list_arduino[6]+127)*2);
    Serial.print("ultrasonic right; ");
    Serial.println((list_arduino[7]+127)*2);
  } else {Serial.print("error");}
  delay(1500);
}
