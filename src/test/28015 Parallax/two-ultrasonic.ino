const int pingPin = 2;
const int pingPin2 = 3;
const int ledPin = 13;
unsigned long duration;
int cm;

void setup()
{
  pinMode(pingPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
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

  if(cm <= 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

//ピンをOUTPUTに設定（パルス送信のため）
  pinMode(pingPin2, OUTPUT);
  //LOWパルスを送信
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);  
  //HIGHパルスを送信
  digitalWrite(pingPin2, HIGH);  
  //5uSパルスを送信してPingSensorを起動
  delayMicroseconds(5); 
  digitalWrite(pingPin2, LOW); 
  
  //入力パルスを読み取るためにデジタルピンをINPUTに変更（シグナルピンを入力に切り替え）
  pinMode(pingPin2, INPUT);   
  
  //入力パルスの長さを測定
  duration = pulseIn(pingPin2, HIGH);  

  //パルスの長さを半分に分割
  duration=duration/2;  
  //cmに変換
  cm = int(duration/29); 

  if(cm <= 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(100);

  if(cm <= 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  Serial.print(cm);
  Serial.print("cm-2");
  Serial.println();
}