#pragma once
#include <Arduino.h>
#include <SPIFFS.h>

class FileManager {
public:
  bool begin(const char* basePath);
  bool fileExists(const String& filename);
  String readFile(const String& filename);
  bool createFile(const String& filename);
  bool appendToFile(const uint8_t* data, size_t size);
  bool deleteFile(const String& filename);
  String getFileListJson();
  std::vector<String> getFileList();
  
private:
  String _basePath;
  String _currentFilePath;
  File _currentFile;
};
