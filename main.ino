#include<Wire.h> // I2C library

///----------------------------------------------
///----------------------------------------------

int instruction[8] = {5,0,0,0,0,0,0,0};

/// instruction[0] = 2 (LED), others (sensor)
///
///
/// instruction [0] = 4 ==>  check sensors
///
/// instruction [0] = 3 ==>  micro switches
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
int photo_refrector_value = 0;
bool ready_sensor_values = false;

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

  pinMode( 9, OUTPUT );
  pinMode( 10, OUTPUT );
}

//________________________________________________________________________________

void loop(){
  if (instruction[0] == 3 && !ready_sensor_values)
  {
    photo_refrector_value = analogRead(A6) / 10;

    int left_ultrasonic_cm,right_ultrasonic_cm = 0;
    left_ultrasonic_cm = ultrasonic_sensor(9,1);
    right_ultrasonic_cm = ultrasonic_sensor(10,2);
    ready_sensor_values = true;
  }
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
    if (instruction[1] == 1) // マイクロスイッチ 3-1----------------------------
    {
      byte temp_sensor[2] = {0,0};
      microswitches();
      temp_sensor[0] = microswitches_condition[0];
      temp_sensor[1] = microswitches_condition[1];

      Wire.write(temp_sensor, 2);
      Serial.print("Value: ");
      Serial.print(temp_sensor[0]);
      Serial.println(temp_sensor[1]);
    }
    else if (instruction[1] == 2) // 超音波センサー 3-2-------------------------
    {
      Serial.println();
      Wire.write((byte));
    }
    else if (instruction[1] == 3) // フォトリフレクタ 3-3-----------------------
    {
      Serial.println(photo_refrector_value);
      Wire.write((byte)photo_refrector_value);
    }
    ready_sensor_values = false;
  }
  else if (instruction[0] == 4) // 適当なデーターを送ってI2C接続を確認 4_______________
  {
    Serial.println("test");
    byte test_I2C[8] = {0,1,127,byte(-127),1,2,3,4};
    Wire.write(test_I2C, 8);
  }
}
//________________________________________________________________________________
//________________________________________________________________________________

void microswitches() 
{
  microswitches_condition[0] = digitalRead(12);
  microswitches_condition[1] = digitalRead(11); // 11が左、12が右
}
//________________________________________________________________________________

int ultrasonic_sensor(char pingPort,char pingPin)
{
  //-------------------------------------------------------------------------------------
  //  This code is available in case you use pin 9 or 10.
  //  You have to change addresses when you use other pins.
  //      The same applies if you use other boards other than Nano Every.
  //  This code is available under ATMega328 emulation which emulates Arduino Uno
  //
  //  Pin Map: digital pin 9 => PB0, Register => 1, blue seal is on
  //           digital pin 10 => PB1, Register => 2, yellow seal is on
  //-------------------------------------------------------------------------------------

  Serial.println("ultrasonic");
  unsigned long duration, cm;
  int result = 0;

  noInterrupts(); // 割り込み停止-------------------------------------------------------
  //ピンをOUTPUTに設定（パルス送信のため）
  DDRB |= _BV(pingPin); // pinMode(pingPort, OUTPUT);
  //LOWパルスを送信
  PORTB &= ~_BV(pingPin); // digitalWrite(pingPort,LOW);
  delayMicroseconds(2);  
  //HIGHパルスを送信
  PORTB |= _BV(pingPin); // digitalWrite(pingPort, HIGH);
  //5uSパルスを送信してPingSensorを起動
  delayMicroseconds(5); 
  PORTB &= ~_BV(pingPin); // digitalWrite(pingPort,LOW);

  //入力パルスを読み取るためにデジタルピンをINPUTに変更
  DDRB &= ~_BV(pingPin); //pinMode(pingPort, INPUT);

  //入力パルスの長さを測定
  duration = pulseIn(pingPort, HIGH);

  cm = int(duration / 29 / 2); //cmに変換 & パルスの長さを半分に分割 

  if (cm > 10) {
    result = 11;
  } else {
    result = 9;
  }
  interrupts(); // 割り込み開始--------------------------------------------------

  Serial.print("ultrasonic sensor: ");
  Serial.println(result);
  Serial.print(cm);
  Serial.println("cm");
  return result;
  // for(int i = 0; i < 25; i++) {
  //   delayMicroseconds(1000); // 1ms
  // } // wait for 25ms
}

//________________________________________________________________________________

void gyro_sensor() {}
