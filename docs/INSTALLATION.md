# Installation Guide

## Prerequisites

- Arduino IDE 1.8.x or newer
- ESP32-S3 board support installed
- USB cable for flashing
- CardPuter ADV device

## Installation Steps

### 1. Install Arduino IDE

Download from: https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Go to File → Preferences
2. Add this URL to "Additional Boards Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to Tools → Board → Boards Manager
4. Search for "ESP32" and install the latest version

### 3. Install Required Libraries

Go to Sketch → Include Library → Manage Libraries and install:

- **TFT_eSPI** - Display driver
- **WiFi** - WiFi connectivity (built-in with ESP32)
- **SPIFFS** - File system (built-in with ESP32)
- **ArduinoJSON** - JSON parsing

### 4. Configure TFT_eSPI

1. Open the TFT_eSPI library directory
2. Edit `User_Setup.h` with CardPuter display settings:
   ```cpp
   #define ILI9341_DRIVER
   #define TFT_WIDTH 240
   #define TFT_HEIGHT 135
   #define TFT_MISO 13
   #define TFT_MOSI 11
   #define TFT_SCLK 12
   #define TFT_CS 10
   #define TFT_DC 14
   #define TFT_RST 9
   ```

### 5. Clone and Build

```bash
git clone https://github.com/Bubbergamesites/cardputer-html-viewer.git
cd cardputer-html-viewer
```

### 6. Flash to CardPuter

1. Open `app/main.cpp` in Arduino IDE
2. Select Tools → Board → ESP32S3 Dev Module
3. Set appropriate COM port
4. Click Upload

## Troubleshooting

- **Upload fails**: Check USB connection and COM port
- **Display shows nothing**: Verify TFT_eSPI configuration
- **WiFi not working**: Check SSID and password configuration
