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
byte microswitches_condition[2] = {0,0};
int photo_refrector_value = 0;
bool ready_sensor_values = true;
byte Tilt_sensor = 0;
int left_ultrasonic_cm,right_ultrasonic_cm = 0;
byte data_sendtoEV3[8] = {0,0,0,0,0,0,0,0};

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

//____________________________________________________________________________________________________

void loop(){
  if (instruction[0] == 3 && !ready_sensor_values)
  {
    for (int i = 0; i < 8; i += 1) {
      data_sendtoEV3[i] = 0;  // 要素を0で初期化
    }
    
    data_sendtoEV3[0] = instruction[0];
    if (instruction[1] == 1){ // マイクロスイッチ 3-1----------------------------
      microswitches();
      data_sendtoEV3[1] = microswitches_condition[0]; // left
      data_sendtoEV3[2] = microswitches_condition[1]; // right
    }

    if (instruction[1] == 2){ // 超音波センサー 3-2------------------------------
      data_sendtoEV3[1] = ultrasonic_sensor(9,1); // left
      data_sendtoEV3[2] = ultrasonic_sensor(10,2); // right
    }

    if (instruction[1] == 3){ // フォトリフレクタ 3-3----------------------------
      photo_refrector_value = analogRead(A6) / 10;
      data_sendtoEV3[1] = photo_refrector_value;
    }

    if (instruction[1] == 4){ // チルトセンサー 3-4------------------------------
      Tilt_sensor = digitalRead(2);
      data_sendtoEV3[1] = Tilt_sensor;
    }

    ready_sensor_values = true;
    Serial.println("load");
  }
  else if (instruction[0] == 4)// 適当なデーターを送ってI2C接続を確認 4__________
  {
    byte test_I2C[8] = {0,1,127,byte(-127),1,2,3,4};
    for(int i = 0; i < 8; i++) {
      data_sendtoEV3[i] = test_I2C[i];
    }
  }
}

//____________________________________________________________________________________________________
//____________________________________________________________________________________________________
//____________________________________________________________________________________________________

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
  Serial.print(instruction[0]);
  Serial.println(instruction[1]);

  if( instruction[0] == 2 ) // Pin13のLED関係-----------------------------------  
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
}

//____________________________________________________________________________________________________

void requestEvent()
{
  if (instruction[0] != 5)
  {
    Serial.print("request: ");
    Serial.print(instruction[0]);
    Serial.println(instruction[1]);
    Wire.write(data_sendtoEV3,8);
    ready_sensor_values = false;
  }
}
//____________________________________________________________________________________________________
//____________________________________________________________________________________________________

void microswitches()
{
  //-------------------------------------------------------------------------------------
  // Pin Map: digital 11 => PE0, Register => 1, left
  //          digital 12 => PE1, Register => 2, right
  //-------------------------------------------------------------------------------------
  microswitches_condition[0] = digitalRead(12);
  microswitches_condition[1] = digitalRead(11);
}
//____________________________________________________________________________________________________

int ultrasonic_sensor(char pingPort,char pingPin)
{
  //-------------------------------------------------------------------------------------
  //  This code is available in case you use pin 9 or 10.
  //  You have to change addresses when you use other pins.
  //      The same applies if you use other boards other than Nano Every.
  //  This code is available under ATMega328 emulation which emulates Arduino Uno
  //
  //  Pin Map: digital pin 9 => PB0, Register => 1, blue seal is on, left
  //           digital pin 10 => PB1, Register => 2, yellow seal is on, right
  //-------------------------------------------------------------------------------------

  Serial.println("ultrasonic");
  unsigned long duration, cm;
  int result = 0;

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

  duration = pulseIn(pingPort, HIGH); //入力パルスの長さを測定

  cm = int(duration / 29 / 2); //cmに変換 & パルスの長さを半分に分割 

  if (cm > 10) {
    result = 11;
  } else {
    result = 9;
  }

  Serial.print("ultrasonic sensor: ");
  Serial.println(result);
  Serial.print(cm);
  Serial.println("cm");
  return result;

  // delayMicroseconds(200);
}

//____________________________________________________________________________________________________

void gyro_sensor() {}
