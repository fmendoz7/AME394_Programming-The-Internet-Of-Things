/*  Programmer: Francis Mendoza
 *  Assignment: A4
 *  Purpose: Control LED remotely
 */

//Call necessary preprocessor commands
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <ESP8266WiFi.h>

//Wifi credentials
const char* ssid     = "Tejaswi2";
const char* password = "12345678";

/*const char* ssid     = "Vista Del Sol";
const char* password = "HanchiBoy77**";*/

const char* host = "34.222.19.236";
//-----------------------------------------------------------
//METHOD: Setup
void setup() 
{
  Serial.begin(115200);
  delay(10);
    pinMode(D8, OUTPUT);


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

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
      lcd.begin();
      lcd.backlight();
  print2Screen("Line 1 Testing", "Line 2 Testing");
}
//-----------------------------------------------------------
//METHOD: print2Screen
int value = 0;
void print2Screen(String s1, String s2)
{
  lcd.clear();
  lcd.print(s1);
  lcd.setCursor(0,1);
  lcd.print(s2);
}
//-----------------------------------------------------------
//METHOD: Loop
void loop() 
{
  delay(500);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  //WiFiClient to make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  //--------------------------------------------------------------------------------------
  // We now create a URI for the request
  String path = "/getValue";


  Serial.print("Requesting URL: ");
  Serial.println(path);
  //--------------------------------------------------------------------------------------
  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  //--------------------------------------------------------------------------------------
  int lineno = 1;
  // Read lines from server. Gets printed to serial
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    String retvalue = line;
    
    if(lineno == 9)
    {
      lcd.clear();
      int primaryLimit = retvalue.indexOf(',');
      
      String firstLine = retvalue.substring(1, primaryLimit);
      Serial.print(firstLine);
      
      String secondLine = retvalue.substring(primaryLimit+1);
      Serial.print(secondLine);
      print2Screen(firstLine, secondLine);
    }
    lineno = lineno + 1;
  }

  Serial.println();
  Serial.println("closing connection");
}


