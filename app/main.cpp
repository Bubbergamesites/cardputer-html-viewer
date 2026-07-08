#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "display.h"
#include "html_renderer.h"
#include "wifi_manager.h"
#include "file_manager.h"

// Configuration
#define WIFI_SSID "CardPuter"
#define WIFI_TIMEOUT 10000
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135

// Global objects
Display display;
HtmlRenderer renderer;
WiFiManager wifiManager;
FileManager fileManager;
WebServer server(80);

// State variables
char currentFile[256] = "";
bool fileLoaded = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\nCardPuter HTML Viewer Starting...");
  
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  
  // Initialize display
  if (!display.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT)) {
    Serial.println("Display initialization failed");
    return;
  }
  
  display.showMessage("Initializing...");
  
  // Initialize file manager
  fileManager.begin("/files");
  
  // Initialize WiFi
  wifiManager.begin();
  wifiManager.displayCredentials();
  
  // Initialize HTML renderer
  renderer.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  
  // Setup web server routes
  setupWebServer();
  
  Serial.println("CardPuter HTML Viewer Ready!");
  display.showMessage("Ready. Press any button.");
}

void loop() {
  handleInput();
  server.handleClient();
  delay(50);
}

void handleInput() {
  // Handle device button input
  // This will depend on CardPuter's hardware configuration
}

void setupWebServer() {
  // Serve file list
  server.on("/api/files", HTTP_GET, []() {
    String json = fileManager.getFileListJson();
    server.send(200, "application/json", json);
  });
  
  // Upload HTML file
  server.on("/api/upload", HTTP_POST, []() {
    handleFileUpload();
  });
  
  // Get current file content
  server.on("/api/current", HTTP_GET, []() {
    if (strlen(currentFile) > 0) {
      String content = fileManager.readFile(currentFile);
      server.send(200, "text/html", content);
    } else {
      server.send(404, "text/plain", "No file loaded");
    }
  });
  
  // Load file
  server.on("/api/load", HTTP_POST, []() {
    String filename = server.arg("file");
    if (fileManager.fileExists(filename)) {
      strcpy(currentFile, filename.c_str());
      String content = fileManager.readFile(filename);
      renderer.render(content);
      fileLoaded = true;
      server.send(200, "text/plain", "File loaded");
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });
  
  server.begin();
}

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    Serial.printf("Upload Start: %s\n", filename.c_str());
    fileManager.createFile(filename);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    fileManager.appendToFile((const uint8_t*)upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.printf("Upload End: %d bytes\n", upload.totalSize);
    server.send(200, "text/plain", "Upload successful");
  }
}
