#pragma once

void exit(const char* param1, const char* param2, const char* param3) {
  Serial.println("Exiting...");
  delay(1000);
  Serial.end();
}