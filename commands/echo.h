#pragma once

void echo(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: please enter word to echo");
    return;
  }
  Serial.println(param1);
}