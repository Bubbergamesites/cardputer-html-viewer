#include "file_manager.h"
#include <vector>

bool FileManager::begin(const char* basePath) {
  _basePath = basePath;
  
  // Create base directory if it doesn't exist
  if (!SPIFFS.exists(_basePath)) {
    Serial.printf("Creating directory: %s\n", _basePath);
    // SPIFFS doesn't support directories, so we'll use the path as prefix
  }
  
  Serial.printf("File Manager initialized with base path: %s\n", _basePath);
  return true;
}

bool FileManager::fileExists(const String& filename) {
  String fullPath = _basePath + "/" + filename;
  return SPIFFS.exists(fullPath);
}

String FileManager::readFile(const String& filename) {
  String fullPath = _basePath + "/" + filename;
  
  if (!SPIFFS.exists(fullPath)) {
    Serial.printf("File not found: %s\n", fullPath.c_str());
    return "";
  }
  
  File file = SPIFFS.open(fullPath, "r");
  if (!file) {
    Serial.printf("Failed to open file: %s\n", fullPath.c_str());
    return "";
  }
  
  String content = "";
  while (file.available()) {
    content += (char)file.read();
  }
  
  file.close();
  return content;
}

bool FileManager::createFile(const String& filename) {
  String fullPath = _basePath + "/" + filename;
  
  File file = SPIFFS.open(fullPath, "w");
  if (!file) {
    Serial.printf("Failed to create file: %s\n", fullPath.c_str());
    return false;
  }
  
  _currentFilePath = fullPath;
  _currentFile = file;
  return true;
}

bool FileManager::appendToFile(const uint8_t* data, size_t size) {
  if (!_currentFile) {
    return false;
  }
  
  size_t written = _currentFile.write(data, size);
  return written == size;
}

bool FileManager::deleteFile(const String& filename) {
  String fullPath = _basePath + "/" + filename;
  
  if (SPIFFS.remove(fullPath)) {
    Serial.printf("File deleted: %s\n", fullPath.c_str());
    return true;
  } else {
    Serial.printf("Failed to delete file: %s\n", fullPath.c_str());
    return false;
  }
}

String FileManager::getFileListJson() {
  std::vector<String> files = getFileList();
  String json = "[";
  
  for (size_t i = 0; i < files.size(); i++) {
    json += "\"" + files[i] + "\"";
    if (i < files.size() - 1) {
      json += ",";
    }
  }
  
  json += "]";
  return json;
}

std::vector<String> FileManager::getFileList() {
  std::vector<String> files;
  File root = SPIFFS.open(_basePath);
  
  if (!root) {
    Serial.printf("Failed to open directory: %s\n", _basePath.c_str());
    return files;
  }
  
  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      String filename = file.name();
      // Remove base path from filename
      if (filename.startsWith(_basePath)) {
        filename = filename.substring(_basePath.length());
      }
      files.push_back(filename);
    }
    file = root.openNextFile();
  }
  
  return files;
}
