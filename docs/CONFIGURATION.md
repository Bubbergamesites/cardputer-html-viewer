# Configuration Guide

## WiFi Configuration

### Setting Up WiFi

Edit `app/main.cpp` and modify:

```cpp
#define WIFI_SSID "YourSSID"
#define WIFI_TIMEOUT 10000
```

### WiFi Modes

1. **Station Mode**: Connect to existing WiFi network
2. **AP Mode**: Create access point on the device

## Display Configuration

### Screen Resolution

CardPuter ADV has a 2.4" display with resolution 240x135:

```cpp
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135
```

## File Storage

### SPIFFS Configuration

Files are stored in SPIFFS filesystem:

- Base path: `/files/`
- Max file size: Limited by SPIFFS partition
- Supported formats: HTML, CSS, JavaScript, images

### Directory Structure

```
/
├── files/
│   ├── index.html
│   ├── style.css
│   └── script.js
└── config/
    └── wifi.conf
```

## Performance Tuning

### Memory Management

- ESP32-S3 has 8MB PSRAM
- Optimize file caching
- Use PROGMEM for static content

### Display Refresh Rate

Default: 60 FPS
Adjust in `display.cpp`:

```cpp
delay(16); // ~60 FPS
```

## Advanced Configuration

### Custom CSS Support

Edit `app/html_renderer.cpp` to add more CSS properties:

```cpp
std::map<String, String> cssProperties;
```

### JavaScript Engine

For basic JS support, consider integrating:
- Duktape (lightweight)
- QuickJS (advanced)

## Debugging

Enable debug mode in serial output:

```cpp
#define DEBUG 1
```

All debug messages will be printed to Serial at 115200 baud.
