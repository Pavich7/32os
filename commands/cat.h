void cat(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("cat <filename> - read a file.");
    return;
  }
  String path = "/" + String(param1);
  readFile(SPIFFS, path.c_str());
}