#pragma once

void edit(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("edit <filename> <content> [append] - edit a file.");
    return;
  }
  String path = "/" + String(param1);
  if (param2 == nullptr || strlen(param2) == 0) {
    Serial.println("Usage: edit <filename> <content> [append]");
    return;
  }
  if (param3 != nullptr && strcmp(param3, "append") == 0) {
    Serial.printf("Appending to file: %s\r\n", path.c_str());
    File file = SPIFFS.open(path.c_str(), FILE_APPEND);
    if (!file) {
      Serial.println("Failed to open file for appending");
      return;
    }
    if (file.print(param2)) {
      Serial.println("File appended");
    } else {
      Serial.println("Append failed!");
    }
    file.close();
    return;
  }
  writeFile(SPIFFS, path.c_str(), param2);
}
