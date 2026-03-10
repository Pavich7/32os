#pragma once

void touch(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0 || param2 == nullptr || strlen(param2) == 0) {
    Serial.println("touch <filename> <content> - create a file.");
    return;
  }
  String path = "/" + String(param1);
  writeFile(SPIFFS, path.c_str(), param2);
}