#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Connect to D1 and D2 on nodemcu


#include <SimpleDHT.h>
int pinDHT11 = D4;
SimpleDHT11 dht11(pinDHT11);


#include <ESP8266WiFi.h>
const char* ssid     = "Tejaswi";
const char* password = "12345678";
const char* host = "52.12.175.60";



void setup()
{
  Serial.begin(115200);
	// initialize the LCD
	lcd.begin();
  print2Screen("LOADING .....", "");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void print2Screen(String s1, String s2){
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(s1);
  lcd.setCursor(0,1);
  lcd.print(s2);
}

float t = 0;
float h = 0;

void loop()
{

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  t = (float)temperature*1.8+32;
  h = (float)humidity;
  



  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String path = "/setValue?t=" + String(t) + "&h=" + String(h);


  Serial.print("Requesting URL: ");
  Serial.println(path);

  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.println(line.length());
    Serial.print(line);
    int val = line.toInt();
  }

  Serial.println();
  Serial.println("closing connection");

   print2Screen("TEMP: " + String(t) + " *F", "HUM : " + String(h) + " %");

  
  // DHT11 sampling rate is 1HZ.
  delay(500);  
}
