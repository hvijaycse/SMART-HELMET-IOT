
#include <ESP8266WiFi.h>

int pin = 5;
int temp ;
int buzz = 14; //D5

char ssid[] = "JECRCAP1234";           // SSID of your AP
char pass[] = "123456789";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,HIGH);
  delay(300);
  digitalWrite(buzz,LOW);
  pinMode(pin, INPUT);
}

void loop() {
//  int temp1;
  temp = digitalRead(pin);
 // temp1 = temp;
  
  if(temp == 1)
  {
  //delay(500);
  client.connect(server, 80);
  Serial.print("Temp =");
  Serial.print(temp);
  Serial.println();
  delay(20);
 
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print("H\r"));
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  client.flush();
  //digitalWrite(pin, HIGH);
  client.stop();
  delay(50);while(client.available()){
 String line = client.readStringUntil('\r');
 Serial.print(line);
  }
 
 //Close the Connection. Automatically
 Serial.println();
 Serial.println("closing connection");
 delay(10);
 //End if
//End Loop

  }
}
