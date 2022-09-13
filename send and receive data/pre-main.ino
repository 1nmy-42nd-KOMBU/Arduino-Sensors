#include<Wire.h> // I2C library

const int pingPin = 2;
unsigned long duration;
int cm;

//________________________________________________________________________________
void setup()
{
    Wire.begin(0x04); // set the slave address
    Wire.onRequest(requestEvent); // Sending information back to the NXT/EV3
    pinMode(13, OUTPUT); // LED
    pinMode(12, INPUT_PULLUP); // MicroSwitch 1
    pinMode(11, INPUT_PULLUP); // MicroSwitch 2

    pinMode(pingPin, OUTPUT);
    
    // Debugging
    Serial.begin(9600);
}

//________________________________________________________________________________
void loop()
{
    delay(5);
}

//________________________________________________________________________________
void requestEvent()
{
    byte temp_sensor[2] = {digitalRead(12), digitalRead(11)};
    int tmp_sensor[2] = {digitalRead(12), digitalRead(11)};
    Wire.write(temp_sensor, 2); // respond with message
    Serial.print("Value: ");
    Serial.print(tmp_sensor[0]);
    Serial.println(tmp_sensor[1]);

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

    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    delay(25);
}//end requestEvent

//________________________________________________________________________________
