#include <SoftwareSerial.h>
#include <Wire.h>


SoftwareSerial BTSerial(2, 3);  //TX, RX

#define Addr 0x1E               // 7-bit address of HMC5883 compass


int val = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(13, OUTPUT);  //red
  pinMode(6, OUTPUT);   //yellow
  pinMode(5, OUTPUT);   //blue
  digitalWrite(13, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);

  pinMode(9, INPUT);

  delay(100);

  Wire.begin();
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}

void loop() {

  int x, y, z;

  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.write(data);

    if (data == '0') {
      digitalWrite(13, HIGH);
    } else if (data == '1') {
      digitalWrite(13, LOW);
    }  else if (data == '2') {
      digitalWrite(6, HIGH);
    }  else if (data == '3') {
      digitalWrite(6, LOW);
    }  else if (data == '4') {
      digitalWrite(5, HIGH);
    }  else if (data == '5') {
      digitalWrite(5, LOW);
    }
  }

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(0x03);       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis

  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    Serial.println("wire read");
  }
  
  // Print raw values
  Serial.print("X=");
  Serial.print(x);
  Serial.print(", Y=");
  Serial.print(y);
  Serial.print(", Z=");
  Serial.println(z);


  val = analogRead(A0);
  if(val > 500) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  //if (Serial.available()){
    //BTSerial.write(Serial.read());
    BTSerial.print("01 ");
    BTSerial.print(val);
    Serial.println(val);

    delay(1000);
  //}
}