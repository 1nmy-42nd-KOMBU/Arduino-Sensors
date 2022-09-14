import processing.serial.*;

Serial serial;
String v = "";
int lf = 10;

void setup() 
{
  println(Serial.list()[1]);
  
  size(200, 150);
  frameRate(30);
  
  serial = new Serial(this, Serial.list()[1], 9600);
  serial.bufferUntil(lf);
}

void draw()
{
  background(255, 255, 255);
  
  if(v != null) {
    fill(0, 0, 255);
    textSize(28);
    textAlign(CENTER);
    text(v, 100, 75);
  }
}

void serialEvent(Serial p) {
  if (serial.available() >= 2) 
  {
     v = p.readString();    
  }
}
