#include<Wire.h> // I2C library

//________________________________________________________________________________
const int pingPin = 2;
const int ledPin = 13;
unsigned long duration;
int cm;
int ultrasonic;

void setup()
{
    Wire.begin(0x04); // set the slave address
    Wire.onRequest(requestEvent); // Sending information back to the NXT/EV3
    pinMode(13, OUTPUT); // LED
    pinMode(12, INPUT_PULLUP); // MicroSwitch 1
    pinMode(11, INPUT_PULLUP); // MicroSwitch 2

    pinMode(pingPin, OUTPUT); // ultrasonic

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
    digitalWrite(ledPin, HIGH);

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

    if(cm <= 20) {
        ultrasonic = 1; // 20cm以内なら1 でなければ2を返す
    } else {
        ultrasonic = 0;
    }

    byte temp_sensor[3] = {digitalRead(12), digitalRead(11),ultrasonic};
    Wire.write(temp_sensor, 3); // respond with message
    Serial.print("Value: ");
    Serial.print(temp_sensor[0]);
    Serial.println(temp_sensor[1]);

    digitalWrite(ledPin, LOW);

}//end requestEvent

//________________________________________________________________________________
