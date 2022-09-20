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

int microswitches_condition[2] = {0, 0};
float gyro_angles[3] = {0, 0, 0};

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
  int x = Wire.read(); // Read the last dummy byte (has no meaning, but must read it)

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
  if (instruction[0] == 3)
  {
    byte temp_sensor[2] = {0,0};

    if (instruction[0] == 1) // マイクロスイッチ
    {
      microswitches();
      temp_sensor[0] = microswitches_condition[0];
      temp_sensor[1] = microswitches_condition[1];
    }

    Wire.write(temp_sensor, 2); // respond with message
    Serial.print("Value: ");
    Serial.print(temp_sensor[0]);
    Serial.println(temp_sensor[1]);
  }
  else if (instruction[0] == 4) // 適当なデーターを送ってI2C接続を確認
  {
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

int ultrasonic_sensor(int pin)
{
  unsigned long duration;
  int cm;
  const int pingPin = 2;

  if (pin == 3)
  {
    pingPin = 3;
  }

  //ピンをOUTPUTに設定（パルス送信のため）
  pinMode(pingPin, OUTPUT);
  //LOWパルスを送信
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);  
  //HIGHパルスを送信
  digitalWrite(pingPin, HIGH);  
  //5uSパルスを送信してPingSensorを起動
  delayMicroseconds(5); 
  digitalWrite(pingPin, LOW); 
  
  //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
  pinMode(pingPin, INPUT);   
  
  //入力パルスの長さを測定
  duration = pulseIn(pingPin, HIGH);  

  //パルスの長さを半分に分割
  duration=duration/2;  
  //cmに変換
  cm = int(duration/29); 
  
  Serial.println(cm);
  return cm;
}
//________________________________________________________________________________

int photo_refrector()
{
  int val = analogRead(A6);
  Serial.println(val);
  return val;
}
//________________________________________________________________________________

void gyro_sensor() {}
