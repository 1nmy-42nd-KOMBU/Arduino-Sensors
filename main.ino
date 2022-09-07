// I2C Slave Send / Receive
// How to send data from the LEGO Mindstorms NXT/EV3 to the Arduino.
// For LEGO Mindstorms
// Demonstrates how to connect a LEGO MINDSTORMS to an Arduino and Send commands,
// receive data.
// A4 – SDA
// A5 – SCL
// See www.dexterindustries.com/howto for more information on the physical setup.
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________

#include<Wire.h> // I2C library

///----------------------------------------------
///----------------------------------------------

int instruction[5] = {5,0,0,0,0};

/// instruction[0] = 1 (LED), 2 (servo motor} ,3 (DC motor), 4 (sensor)
///
///
/// instruction [0] = 1 ==>  instruction [1] is port (LED digital pin)
///                          instruction [2] is: 0 (LED off) or 1 (LED on)
///
/// instruction [0] = 2 ==>  instruction [1] is port (servo motor number)
///                          instruction [2] is angle
///
/// instruction [0] = 3 ==>  instruction [1] is pin1 number 
///                          instruction [2] is pin1 speed (0-99)
///                          instruction [3] is pin2 number 
///                          instruction [4] is pin2 speed (0-99)  
///
/// instruction [0] = 4 ==>  instruction [1] is pin number
///                          instruction [2] is: 0 (analog pin) or 1 (digital pin)
///                    

//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________

int temp_sensor = 0;

void setup()
{
  Wire.begin(0x04); // set the slave address
  Wire.onRequest(requestEvent); // Sending information back to the NXT/EV3
  Wire.onReceive(receiveI2C); // Receiving information!
  
  // Debugging
  Serial.begin(9600);
}

//________________________________________________________________________________
void loop()
{
  delay(50);      
}

//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________

byte read_byte = 0x00;
int byte_count = 0;


// When data is received from NXT/EV3, this function is called.
void receiveI2C(int bytesIn)
{
  read_byte = bytesIn;
  byte_count = 0;
  while(1 < Wire.available()) // loop through all but the last
  {
    read_byte = Wire.read(); 
    
    instruction[byte_count] = read_byte;
    
    byte_count++;
  }
  int x = Wire.read(); 
  // Read the last dummy byte (has no meaning, but must read it)

  if( instruction[0] == 1 )  
  {
    Serial.println("  Light ");
    
    Serial.print("Pin: "); 
    Serial.println(instruction[1]);
    pinMode(instruction[1], OUTPUT);
    
    Serial.print("State: ");
    if(instruction[2] == 0) 
    {
      Serial.print("off");
      digitalWrite(instruction[1], LOW);
    }
    else                    
    {
      Serial.println("on");
      digitalWrite(instruction[1], HIGH);
    }
  }
  else if( instruction[0] == 4 )  
  {
    Serial.println("  Sensor "); 
    
    Serial.print("Pin: "); 
    Serial.print(instruction[1]);
    
    if ( instruction[2] == true )
    {
      Serial.println("Analog");
      
      int temp_pin = A0;
      if (instruction[1] !=0 )  temp_pin += instruction[1];
      
      temp_sensor = analogRead(temp_pin);
    }
    else
    {
      Serial.println("Digital");
      pinMode(instruction[1], INPUT);
      temp_sensor = digitalRead(instruction[1]);
    }
  }
}//end recieveI2C

//________________________________________________________________________________

void requestEvent()
{  
  if (instruction[0] == 4)
  {
    Wire.write(temp_sensor); // respond with message
    Serial.print("Value: ");
    Serial.println(temp_sensor);
  } 
}//end requestEvent
//________________________________________________________________________________
