#include<Wire.h> // I2C library

//________________________________________________________________________________
void setup()
{
    Wire.begin(0x04); // set the slave address
    Wire.onRequest(requestEvent); // Sending information back to the NXT/EV3
    pinMode(13, OUTPUT); // LED
    pinMode(12, INPUT_PULLUP); // MicroSwitch 1
    pinMode(11, INPUT_PULLUP); // MicroSwitch 2
    
    // Debugging
    Serial.begin(9600);
}

//________________________________________________________________________________
void loop()
{
    delay(50);
}

//________________________________________________________________________________
void requestEvent()
{
    int temp_sensor[2] = {digitalRead(12), digitalRead(11)};
    Wire.write(temp_sensor, 2); // respond with message
    Serial.print("Value: ");
    Serial.println(temp_sensor);
}//end requestEvent

//________________________________________________________________________________
