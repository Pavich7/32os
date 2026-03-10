#pragma once

void uname(const char* param1, const char* param2, const char* param3) {
  Serial.print("32os version ");
  Serial.println(VERSION);
  const char compile_timestamp[] = __DATE__ " " __TIME__;
  Serial.print("Compiled on: ");
  Serial.println(compile_timestamp);
  Serial.print("SDK Version: ");
  Serial.println(esp_get_idf_version());
}