#pragma once

void reboot(const char* param1, const char* param2, const char* param3) {
  Serial.println("Rebooting...");
  delay(1000);
  ESP.restart();
}