#pragma once
#include <Arduino.h>
#include <WiFi.h>

class WiFiManager {
public:
  bool begin();
  bool connect(const char* ssid, const char* password);
  bool isConnected();
  void displayCredentials();
  String getLocalIP();
  void scan();
  void disconnect();
  
private:
  const char* _ssid;
  const char* _password;
  bool _connected;
  uint8_t _retries;
};
