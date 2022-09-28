#include<Wire.h> // I2C library

///----------------------------------------------
///----------------------------------------------

int instruction[8] = {5,0,0,0,0,0,0,0};

/// instruction[0] = 2 (LED), others (sensor)
///
///
/// instruction [0] = 4 ==>  check senesors
///
/// instruction [0] = 3 ==>  microswitches
///
/// instruction [0] = 2 ==>  instruction [1] is port (LED digital pin)
///                          instruction [2] is: 0 (LED off) or 1 (LED on)
///
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________

float gyro_angles[3] = {0, 0, 0};
byte temp[2] = {0,0};
byte microswitches_condition[2] = {0,0};

void setup()
{
  Wire.begin(0x04); // set the slave address
  Wire.onRequest(requestEvent); // Sending information back to the NXT/EV3
  Wire.onReceive(receiveI2C); // Receiving information!
  pinMode(13, OUTPUT); // LED
  
  // Debugging
  Serial.begin(9600);

  pinMode( 11, INPUT_PULLUP );
  pinMode( 12, INPUT_PULLUP );

  pinMode( 10, OUTPUT );
  digitalWrite(10,HIGH);
}

//________________________________________________________________________________
void loop(){}

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
  int x = Wire.read(); // Read the last dummy byte (has no meaning, but must read it)

  Serial.print("Mode: ");
  Serial.println(instruction[0]);

  if( instruction[0] == 2 )  
  {
    Serial.println("  Light ");
    
    Serial.print("Pin: "); 
    Serial.println(instruction[1]);
    
    Serial.print("State: ");
    if(instruction[2] == 0) 
    {
      Serial.println("off");
      digitalWrite(instruction[1], LOW);
    }
    else                    
    {
      Serial.println("on");
      digitalWrite(instruction[1], HIGH);
    }
  }
}//end recieveI2C

//________________________________________________________________________________

void requestEvent()
{  
  Serial.print("request: ");
  Serial.print(instruction[0]);
  Serial.println(instruction[1]);

  if (instruction[0] == 3)
  {
    byte temp_sensor[2] = {0,0};

    if (instruction[1] == 1) // マイクロスイッチ
    {
      microswitches();
      temp_sensor[0] = microswitches_condition[0];
      temp_sensor[1] = microswitches_condition[1];

      Wire.write(temp_sensor, 2); // respond with message
      Serial.print("Value: ");
      Serial.print(temp_sensor[0]);
      Serial.println(temp_sensor[1]);
    }
    else if (instruction[1] == 2)
    {
      int val = ultrasonic_sensor();
      Wire.write(byte(val));
      Serial.println(val);
    }
  }
  else if (instruction[0] == 4) // 適当なデーターを送ってI2C接続を確認
  {
    Serial.println("test");
    byte test_I2C[8] = {0,1,127,byte(-127),1,1,1,1};
    Wire.write(test_I2C, 8);
  }
}//end requestEvent
//________________________________________________________________________________
//________________________________________________________________________________

void microswitches() 
{
  microswitches_condition[0] = digitalRead(12);
  microswitches_condition[1] = digitalRead(11); // 11が左、12が右
}
//________________________________________________________________________________

int ultrasonic_sensor()
{
  Serial.println("ultrasonic");
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;
  int pingPin = 2;
  int result = 0;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = duration / 29 / 2;

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  Serial.print("You should wait for 100 ms");
  // delay(100);
  unsigned long time_now = millis();
  while(millis() < time_now + 100){}//wait approx. [period] ms 
  Serial.print("done well");

  int tmp = (int)cm;

  if (tmp > 10) {
    result = 11;
  } else {
    result = 9;
  }
  Serial.print("result: ");
  Serial.println(result);
  return result;
}

//________________________________________________________________________________

void gyro_sensor() {}
