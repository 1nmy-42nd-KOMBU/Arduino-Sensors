const int pingPin = 1;
const int pingPort = 9;
unsigned long duration;
int cm;
#define OUTPUT_power 0

void setup()
{
  pinMode(pingPin, OUTPUT);
  Serial.begin(9600);
}

//---------------------------------------------------------------------------
//  This code is available in case you use pin 9 or 10.
//  You have to change addresses when you use other pins.
//      The same applies if you use othre borads other than Nano Every.
//
//  Pin Map: digital pin 9 => PB0 blue
//           digital pin 10 => PB1 yellow
//---------------------------------------------------------------------------

void loop()
{
  unsigned long time_begin = micros();
  for(int i = 0; i < 100; i++) {
    //ピンをOUTPUTに設定（パルス送信のため）
    DDRB |= _BV(pingPin); // pinMode(pingPort, OUTPUT); //
    //LOWパルスを送信
    PORTB &= ~_BV(pingPin); // digitalWrite(pingPort,LOW); // 
    delayMicroseconds(2);  
    //HIGHパルスを送信
    PORTB |= _BV(pingPin); // digitalWrite(pingPort, HIGH); //
    //5uSパルスを送信してPingSensorを起動
    delayMicroseconds(5); 
    PORTB &= ~_BV(pingPin); // digitalWrite(pingPort,LOW); // 
    
    //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
    DDRB &= ~_BV(pingPin); //pinMode(pingPort, INPUT); // 
    
    //入力パルスの長さを測定
    duration = pulseIn(pingPort, HIGH);  

    //パルスの長さを半分に分割
    duration=duration/2;  
    //cmに変換
    cm = int(duration/29); 
    
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    for(int i = 0; i < 25; i++) {
      delayMicroseconds(1000); // 1ms
    } // wait for 100ms
  }
  Serial.println(micros() - time_begin);
  delay(100000000000);
}
