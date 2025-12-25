void help(const char* param1, const char* param2, const char* param3) {
  Serial.println("help - show list of commands.");
  Serial.println("echo - echo input text.");
  Serial.println("wlan - manage WLAN settings.");
  Serial.println("reboot - reboot the system.");
  Serial.println("exit - exit the serial.");
  Serial.println("system - manage system settings.");
  Serial.println("clear - clear the screen.");
}