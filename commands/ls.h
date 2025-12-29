#include "system/filesystem.h"

void ls(const char* param1, const char* param2, const char* param3) {
  listDir(SPIFFS, "/", 0);
  Serial.println();
  Serial.print("Free bytes: ");
  Serial.print(SPIFFS.totalBytes() - SPIFFS.usedBytes());
  Serial.print(" (");
  Serial.print(100-((SPIFFS.totalBytes() - SPIFFS.usedBytes()) * 100 / SPIFFS.totalBytes()));
  Serial.println("%)");
  Serial.println();
  Serial.print("Used bytes: ");
  Serial.println(SPIFFS.usedBytes());
  Serial.print("Total bytes: ");
  Serial.println(SPIFFS.totalBytes());
}