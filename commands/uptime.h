#pragma once

void uptime(const char* param1, const char* param2, const char* param3) {
  unsigned long ms = millis();
  unsigned long seconds = ms / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours   = minutes / 60;
  unsigned long days    = hours / 24;
  seconds %= 60;
  minutes %= 60;
  hours   %= 24;
  Serial.print("Uptime: ");
  Serial.print(days);
  Serial.print("d ");
  Serial.print(hours);
  Serial.print("h ");
  Serial.print(minutes);
  Serial.print("m ");
  Serial.print(seconds);
  Serial.println("s");

}