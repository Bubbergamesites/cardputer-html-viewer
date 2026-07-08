#include "display.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

bool Display::begin(uint16_t width, uint16_t height) {
  _width = width;
  _height = height;
  
  initializeHardware();
  setupTFT();
  
  Serial.printf("Display initialized: %dx%d\n", width, height);
  return true;
}

void Display::initializeHardware() {
  // Initialize SPI and GPIO pins for CardPuter
  // These pins need to be configured based on the actual hardware
}

void Display::setupTFT() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}

void Display::showMessage(const char* message) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString(message, _width / 2 - (strlen(message) * 6), _height / 2);
  refresh();
}

void Display::renderHtml(const String& html, const String& css, const String& js) {
  // Render HTML with CSS styling
  // This is a simplified implementation
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.drawString(html.c_str(), 0, 0, 2);
  refresh();
}

void Display::clear() {
  tft.fillScreen(TFT_BLACK);
}

void Display::refresh() {
  // Update display buffer (if needed)
}
