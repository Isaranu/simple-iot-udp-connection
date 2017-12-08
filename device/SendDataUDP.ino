/*
This code compatible for ESP32
Test run with ThaiEasyElec's ESPino32
Coding : J.Isaranu | IoTtweet.com
*/

#include <WiFi.h>
#include <WiFiUdp.h>

const char * ssid = "your-ssid";
const char * passw = "your-password";

const char * udpAddress = "xx.xxx.xxx.xxx"; // Google Cloud Server IP
const int udpPort = 41234; // Google Cloud UDP opened port
String devname = "deviceName"; // name of using device.

char incomingPacket[255];
char payload[255];

bool conn = false;

WiFiUDP udp;

void setup(){
  Serial.begin(115200);

  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, passw);

  Serial.println("Waiting for WIFI connect...");
  delay(3000);
}

void loop(){

  /* Send data to server */
  if(conn){
    
    uint8_t testRand = random(20,30); // Dummy data sending.
    String message = "{\"device\":\"" + String(devname) + "\",\"data\":\"" + String(testRand) + "\"}";
    Serial.println("-------------------------------");
    Serial.println(message);
    
    message.toCharArray(payload, 255);
    
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("%s", payload);
    udp.endPacket();
  }

  /* Receive from server */
  int packetSize = udp.parsePacket();
  Serial.println("[packet receive size] : " + String(packetSize));
  
  if(packetSize){
    
    int len = udp.read(incomingPacket, 255);
    if(len > 0){
        Serial.println("[Response from server] : " + String(incomingPacket));          
      }
    }

   delay(1000);    
}

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          udp.begin(WiFi.localIP(),udpPort);
          conn = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          conn = false;
          break;
    }
}
