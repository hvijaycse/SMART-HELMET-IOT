#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306.h" 
SSD1306  display(0x3c, D3, D5);
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 5;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("JECRCAP1234", "123456789");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();

  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
 

   display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

   display1();
  display.display();
  delay(1000);
  
}

void loop() {
  
  
  WiFiClient client = server.available();

  
  if (!client) {

   delay(50);
   digitalWrite(ledPin, HIGH);
    
     display1();
  display.display();
  delay(1000);
  return;
    
    }
  
  String request = client.readStringUntil('\r');
  if(request=="H"){
    digitalWrite(ledPin, LOW);
    
  }
  else {
    digitalWrite(ledPin, HIGH);
    
  }
  Serial.println(server.available());
  Serial.println(request);
  Serial.println("From the station: " + request);
  client.flush();
  Serial.print("Byte sent to the station: ");
  Serial.println(client.println(request + "A" + "\r"));
  
  

  
   display2();
  display.display();
  delay(1000);
}

void display1(){
 
    display.clear(); // clearing the display
    display.drawString(5,0, "Please use \n");
    display.drawString(5,20,"HELMET !");
   return;
}

void display2(){
 
    display.clear(); // clearing the display
    display.drawString(5,0, "Helmet \n");
    display.drawString(5,20,"Used... !");
   return;
}
