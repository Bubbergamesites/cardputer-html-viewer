# CardPuter HTML Viewer

A comprehensive HTML file viewer for the CardPuter ADV device with support for CSS, JavaScript, and WiFi connectivity.

## Features

- **HTML Rendering**: Full support for HTML5 markup
- **CSS Styling**: CSS2/CSS3 support for beautiful layouts
- **JavaScript Execution**: Interactive JavaScript functionality
- **WiFi Connectivity**: Download and browse HTML files over WiFi
- **File Management**: Browse and open HTML files from device storage
- **Responsive Display**: Optimized for CardPuter's screen resolution
- **Offline Support**: Cache and view downloaded files offline

## Project Structure

```
cardputer-html-viewer/
├── firmware/           # Firmware and device-specific code
├── app/               # Main application code
├── html/              # HTML/CSS/JS templates and assets
├── docs/              # Documentation
├── examples/          # Example HTML files
└── scripts/           # Build and deployment scripts
```

## Requirements

- CardPuter ADV device
- ESP32-S3 (or compatible microcontroller)
- WiFi capability
- 2.4" LCD display support

## Getting Started

1. Clone the repository
2. Install dependencies (see INSTALLATION.md)
3. Configure WiFi settings in `config/wifi.conf`
4. Build and flash the firmware
5. Upload HTML files to the device

## Usage

### Basic Navigation
- Use device buttons to navigate through files
- Select HTML files to view
- Use WiFi to download new files

### Adding HTML Files
1. Connect via USB or WiFi
2. Copy HTML files to `/files` directory
3. Refresh file list in the viewer

## Configuration

See `docs/CONFIGURATION.md` for detailed setup options.

## License

MIT License - See LICENSE file for details

## Contributing

Contributions are welcome! Please read CONTRIBUTING.md for guidelines.
