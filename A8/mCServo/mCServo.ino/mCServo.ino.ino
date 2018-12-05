#include <Servo.h>
Servo needle;

int needleValT = 0;
int needleValH = 0;

int tLight = D6;
int hLight = D8;

#include <SimpleDHT.h>
int pinDHT11 = D4;
SimpleDHT11 dht11(pinDHT11);

float t = 0;
float h = 0;

void setup() 
{
  Serial.begin(115000);
  needle.attach(D7);

  pinMode(tLight, OUTPUT);
  pinMode(hLight, OUTPUT);

  pinMode(D3, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
}

  int buttonHState = 0;
  int buttonTState = 0;

void loop() 
{
  // put your main code here, to run repeatedly:
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");

  t = (float)temperature * 1.8 + 32;
  h = (float)humidity;

  needleValT = map(t, 0, 100, 30, 150);
  needleValH = map(h, 0, 100, 30, 150);

  int buttonT = digitalRead(D3);
  Serial.println(buttonT);

  int buttonH = digitalRead(D5);
  Serial.println(buttonH);
  
  if (buttonT == 1) {  
    buttonTState = 1;
    buttonHState = 0;
  }

  if (buttonH == 1) {  
    buttonHState = 1;
    buttonTState = 0;
  }

  if(buttonTState == 1){
      needle.write(needleValT);
    digitalWrite(tLight, HIGH);
    digitalWrite(hLight, LOW); 
  }

  else{
    needle.write(needleValH);
    digitalWrite(hLight, HIGH);
    digitalWrite(tLight, LOW);
  }

Serial.println("h");
Serial.println(buttonHState); Serial.println("t");
Serial.println(buttonTState);

}
