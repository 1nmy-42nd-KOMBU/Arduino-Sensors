const int LED_PIN = 13;
const int BUMPER_PIN = 12;
 
void setup()
{
    pinMode( LED_PIN, OUTPUT );
    pinMode( BUMPER_PIN, INPUT_PULLUP );
    Serial.begin(9600);
}
 
void loop() {
  if ( digitalRead( BUMPER_PIN ) == LOW ){
    digitalWrite( LED_PIN, LOW );
    Serial.println("LOW");
  } else {
    digitalWrite( LED_PIN, HIGH );
    Serial.println("HIGH");
  }
    // if( digitalRead( BUMPER_PIN ) == LOW ){
    //     while( digitalRead( BUMPER_PIN ) == LOW ){
    //         delay( 10 );
    //         Serial.println("low");
    //     }
 
    //     digitalWrite( LED_PIN, HIGH );
    //     Serial.println("high");
    // } else {
    //     digitalWrite( LED_PIN, LOW );
    // }
}
