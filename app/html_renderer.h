#pragma once
#include <Arduino.h>

class HtmlRenderer {
public:
  bool begin(uint16_t width, uint16_t height);
  void render(const String& htmlContent);
  void parseAndRender(const String& html, const String& css);
  void executeJavaScript(const String& jsCode);
  void clear();
  
private:
  uint16_t _width;
  uint16_t _height;
  String _currentHtml;
  String _currentCss;
  String _currentJs;
  
  void parseHTML(const String& html);
  void parseCSS(const String& css);
  void renderElements();
};
