#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(57600);
}

void loop() {
  mySerial.write(32);
  Serial.flush();

  bool iftimeout = true;
  unsigned long start_time = millis();
  while (iftimeout) {
    if (mySerial.available() > 0) {
      iftimeout = false;
    }
    if (millis() - start_time > 10) {
      Serial.println("timeout");
      mySerial.write(32);
      Serial.flush();
      start_time = millis();
      continue;
    }
    Serial.println("w");
  }
  int8_t list_arduino = 0;
  list_arduino = mySerial.read();
  while (mySerial.available() > 0) {
    int8_t trash = mySerial.read();
  }
  if (list_arduino == 63 || list_arduino == 64 || list_arduino == 65) {
    Serial.print("t;"); // tof----------------------------
    Serial.println(list_arduino);
  }else{
    Serial.print("e");
  }
  // delay(700);
}
