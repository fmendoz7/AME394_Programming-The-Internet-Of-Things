/*  Programmer: Francis Mendoza
 *  Assignment: A3
 *  Purpose: Webpage to determine LED output
 */
//---------------------------------------------------------------
#include <Arduino.h>

extern "C" {
#include "user_interface.h"
}
//---------------------------------------------------------------
//Wifi Credentials
char * HOSTNAME = "Narnia";
char * WifiPASS = "12345";
//---------------------------------------------------------------
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Hash.h>
//---------------------------------------------------------------
//Proper format for server
ESP8266WebServer server (80);
int led = D8;
//---------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);
  pinMode(D8, OUTPUT);

  // Start Wifi AP
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(HOSTNAME, WifiPASS);

  // handle index -- HTTP Server
  //---------------------------------------------------------------
   //BRIGHTNESS: 10%
  server.on("/10", []() 
  { 
    analogWrite(led, 25.5); 
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  }); 
  //---------------------------------------------------------------
   //BRIGHTNESS: 20%
  server.on("/20", []() 
  {
    analogWrite(led, 51);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
    //BRIGHTNESS: 30%
  server.on("/30", []() 
  {
    analogWrite(led, 76.5);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
    //BRIGHTNESS: 40$
  server.on("/40", []() {
    analogWrite(led, 102);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
    //BRIGHTNESS: 50%
  server.on("/50", []() {
    analogWrite(led, 127.5);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
    //BRIGHTNESS: 60%
  server.on("/60", []() {
    analogWrite(led, 153);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  //BRIGHTNESS: 70%
  server.on("/70", []() {
    analogWrite(led, 178.5);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  //BRIGHTNESS: 80%
  server.on("/80", []() {
    analogWrite(led, 204);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  //BRIGHTNESS: 90%
  server.on("/90", []() {
    analogWrite(led, 229.5);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  //BRIGHTNESS: 100%
  server.on("/100", []() {
    analogWrite(led, 255);
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  //Default
  server.on("/", []() {
    server.send(200, "text/html", "<html><head></head><body>  <a href=\"./10\">10</a>  <br>  <a href=\"./20\">20</a>  <br>  <a href=\"./30\">30</a>  <br>  <a href=\"./40\">40</a>  <br>  <a href=\"./50\">50</a>  <br>  <a href=\"./60\">60</a>  <br>  <a href=\"./70\">70</a>  <br>  <a href=\"./80\">80</a> <br> <a href=\"./90\">90</a> <br> <a href=\"./100\">100</a> </body><html>");
  });
  //---------------------------------------------------------------
  server.begin();
}
//---------------------------------------------------------------
void loop() 
{
  server.handleClient();
}


