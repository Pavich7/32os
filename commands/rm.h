void rm(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("rm <filename> - delete a file.");
    return;
  }
  String path = "/" + String(param1);
  deleteFile(SPIFFS, path.c_str());
}