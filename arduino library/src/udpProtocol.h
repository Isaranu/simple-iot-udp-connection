/*
สร้าง library สำหรับ iot protocol แบบ udp connection
code.isaranu.com
coder : Isaranu Janthong
created : 2017.Dec.11

-- compatible with ESP32 series --

*/

#ifndef udpProtocol_h
#define udpProtocol_h

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiUdp.h"

class udpProtocol {

  public:
    bool init(const char *ssid, const char *passw, const char *udpAddress, int udpPort);
    String send(String message);
    String receive();
    void WiFiEvent(WiFiEvent_t event);

  private:
    const char *_ssid, *_passw, *_udpAddress;
    int _udpPort;
    String _message, _resp;
    bool _conn;
    char _incomingPacket[255], _payload[255];

};

#endif
