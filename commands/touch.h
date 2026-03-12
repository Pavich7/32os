#pragma once

void touch(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("touch <filename> - create a file.");
    return;
  }
  String path = "/" + String(param1);
  writeFile(SPIFFS, path.c_str(), "This is a placeholder content. Use edit command to modify the file.");
}