/*
สร้าง library สำหรับ iot protocol แบบ udp connection
code.isaranu.com
coder : Isaranu Janthong
created : 2017.Dec.11

-- compatible with ESP32 series --

*/

#include "udpProtocol.h"

#define CONN_RETRY_LIMIT 30

WiFiUDP udp;

bool udpProtocol::init(const char *ssid, const char *passw, const char *udpAddress, int udpPort){

  _ssid = ssid;
  _passw = passw;
  _udpAddress = udpAddress;
  _udpPort = udpPort;

  int _cnt = 0;

  WiFi.disconnect(true);
  //WiFi.onEvent(WiFiEvent);
  WiFi.begin(_ssid, _passw);
  Serial.print("WiFi connecting..");

  while((WiFi.status() != WL_CONNECTED) && (_cnt <= CONN_RETRY_LIMIT)){
    delay(200);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED){
    _conn = true;
    Serial.println("Connected !");
    Serial.print("WiFi connected! IP address: ");
    Serial.println(WiFi.localIP());
    udp.begin(WiFi.localIP(),_udpPort);
  }else{
    _conn = false;
    Serial.println("Connection Timeout.");
  }

  return _conn;

}

String udpProtocol::send(String message){

  _message = message;

  if(_conn){

    Serial.println(_message);

    _message.toCharArray(_payload, 255);

    udp.beginPacket(_udpAddress,_udpPort);
    udp.printf("%s", _payload);
    udp.endPacket();
  }

  /* Receive from server */
  int _packetSize = udp.parsePacket();
  Serial.println("[packet receive size] : " + String(_packetSize));

  if(_packetSize){

    int len = udp.read(_incomingPacket, 255);
    if(len > 0){
        Serial.println("[Response from server] : " + String(_incomingPacket));
      }
    }

  return _incomingPacket;

}
