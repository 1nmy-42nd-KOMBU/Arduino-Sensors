void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  delay(1000);                       // wait for a second
  Serial.println("Hello Apple");
}