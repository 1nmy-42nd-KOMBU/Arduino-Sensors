#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); // RX, TX
// this sample code provided by www.programmingboss.com
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() {
  char list[] = {0,1,2,3};
  Serial.println("Hello Boss");
  mySerial.write(list,4);
  
  while (mySerial.available() <= 0){}
  char byte_count = 0;
  int8_t list_arduino[]  = {0,0,0,0};
  Serial.print(mySerial.available());
  while (mySerial.available() > 0) {
    list_arduino[byte_count] = mySerial.read();
    byte_count += 1;
  }
  Serial.print(list_arduino[0]);
  Serial.print(list_arduino[1]);
  Serial.print(list_arduino[2]);
  Serial.println(list_arduino[3]);
    
  delay(1500);
}