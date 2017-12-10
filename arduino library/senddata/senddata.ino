#include "udpProtocol.h"

const char *ssid = "your-ssid";
const char *passw = "your-password";
const char * udpAddress = "xx.xxx.xxx.xxx"; // Google Cloud Server IP
const int udpPort = 41234; // Google Cloud UDP opened port
String devname = "Testlibudp"; // name of using device.

udpProtocol myudp;

void setup() {
  
  Serial.begin(115200);
  myudp.init(ssid,passw,udpAddress,udpPort);

}

void loop() {
  
  uint8_t testRand = random(20,30); // Dummy data sending.
  String test_message = "{\"device\":\"" + String(devname) + "\",\"data\":\"" + String(testRand) + "\"}";
  myudp.send(test_message);

  delay(1000);

}
