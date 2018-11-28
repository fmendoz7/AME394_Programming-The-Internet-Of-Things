#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Connect to D1 and D2 on nodemcu


#include <ESP8266WiFi.h>

const char* ssid     = "Tejaswi";
const char* password = "12345678";

const char* host = "52.24.68.226";


void setup() {
  Serial.begin(115200);
  delay(10);
    lcd.begin();
      lcd.backlight();

    pinMode(D2, OUTPUT);


  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
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

int value = 0;

void loop() {
  delay(500);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String path = "/getValue";


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

  int lineno = 1;
  String S1 = "";
  String S2 = "";
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(lineno);
    Serial.println(line);
    if(lineno == 9){
      S1 = line.substring(1);
    }
    if(lineno == 10){
      S2 = line;
    }

    
    lineno = lineno + 1;
    
  }

    lcd.clear();
    lcd.print(S1);
    lcd.setCursor(0,1);
    lcd.print(S2);

  Serial.println();
  Serial.println("closing connection");
}

