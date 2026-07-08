#include "wifi_manager.h"

bool WiFiManager::begin() {
  Serial.println("WiFi Manager initializing...");
  WiFi.mode(WIFI_STA);
  _connected = false;
  _retries = 0;
  return true;
}

bool WiFiManager::connect(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
  
  Serial.printf("Connecting to WiFi: %s\n", ssid);
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    _connected = true;
    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
    return true;
  } else {
    _connected = false;
    Serial.println("\nConnection failed");
    return false;
  }
}

bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::displayCredentials() {
  Serial.println("\n=== WiFi Information ===");
  Serial.printf("Device Name: CardPuter HTML Viewer\n");
  Serial.printf("MAC Address: %s\n", WiFi.macAddress().c_str());
  Serial.println("============================");
}

String WiFiManager::getLocalIP() {
  if (isConnected()) {
    return WiFi.localIP().toString();
  }
  return "Not connected";
}

void WiFiManager::scan() {
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();
  Serial.printf("Found %d networks\n", n);
  
  for (int i = 0; i < n; ++i) {
    Serial.printf("%d: %s (Signal: %d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}

void WiFiManager::disconnect() {
  if (_connected) {
    WiFi.disconnect(true);
    _connected = false;
    Serial.println("Disconnected from WiFi");
  }
}
