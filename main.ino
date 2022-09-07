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
  if ( digitalRead( MicSw1 ) == 1 && digitalRead( MicSw2 ) == 1 ){
    digitalWrite( LED_PIN, HIGH );
  } else {
    digitalWrite( LED_PIN, LOW );
  }
  delay(500);
    // if( digitalRead( MicSw1 ) == LOW ){
    //     while( digitalRead( MicSw1 ) == LOW ){
    //         delay( 10 );
    //         Serial.println("low");
    //     }
 
    //     digitalWrite( LED_PIN, HIGH );
    //     Serial.println("high");
    // } else {
    //     digitalWrite( LED_PIN, LOW );
    // }
  Serial.print( digitalRead( MicSw2 ) );
  Serial.println( digitalRead( MicSw1 ) );
}
