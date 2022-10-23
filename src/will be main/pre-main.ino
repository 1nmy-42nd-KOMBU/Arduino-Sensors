#include<Wire.h> // I2C library

void setup()
{
  Wire.begin(); // set the slave address
  // Debugging
  Serial.begin(9600);
}

//____________________________________________________________________________________________________

void loop() {
  int knob = 14;
  Wire.beginTransmission(4);         //(6)
  Wire.write(knob); 
  Wire.requestFrom(4, 1);
  if (Wire.available()) {
    byte data = Wire.read();
    Serial.print(data);
  }       //(7)
  Serial.println();
  Wire.endTransmission();        //(8)
  delay(500);
}

