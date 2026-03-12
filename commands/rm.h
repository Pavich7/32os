#pragma once

void rm(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("rm <filename> - delete a file.");
    Serial.println("rm * - delete all files.");
    return;
  }
  if (strcmp(param1, "*") == 0) {
    File root = SPIFFS.open("/");
    if (!root) {
      Serial.println("Failed to open root directory");
      return;
    }
    File file = root.openNextFile();
    while (file) {
      deleteFile(SPIFFS, file.path());
      file = root.openNextFile();
    }
    return;
  }
  String path = "/" + String(param1);
  deleteFile(SPIFFS, path.c_str());
}