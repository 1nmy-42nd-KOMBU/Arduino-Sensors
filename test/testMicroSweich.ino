const int LED_PIN = 13;
const int MicSw1 = 12;
const int MicSw2 = 11;

void setup()
{
    pinMode( LED_PIN, OUTPUT );
    pinMode( MicSw1, INPUT_PULLUP );
    pinMode( MicSw2, INPUT_PULLUP );
    Serial.begin(9600);
}

void loop() {
  // 2つのスイッチが両方押されてたらLEDが光る
    if ( digitalRead( MicSw1 ) == 1 && digitalRead( MicSw2 ) == 1 ){
        digitalWrite( LED_PIN, HIGH );
    } else {
        digitalWrite( LED_PIN, LOW );
    }
    // スイッチの状態を表示
    Serial.print( digitalRead( MicSw2 ) );
    Serial.println( digitalRead( MicSw1 ) );

    delay(500);
}
