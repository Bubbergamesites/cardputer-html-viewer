#pragma once
#include <Arduino.h>

class Display {
public:
  bool begin(uint16_t width, uint16_t height);
  void showMessage(const char* message);
  void renderHtml(const String& html, const String& css, const String& js);
  void clear();
  void refresh();
  
private:
  uint16_t _width;
  uint16_t _height;
  void initializeHardware();
  void setupTFT();
};
