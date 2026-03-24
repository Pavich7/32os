#pragma once

void help(const char* param1, const char* param2, const char* param3) {
  Serial.println("help - show list of commands.");
  Serial.println("echo - echo input text.");
  Serial.println("wlan - manage WLAN settings.");
  Serial.println("reboot - reboot the system.");
  Serial.println("exit - exit the serial.");
  Serial.println("system - manage system settings.");
  Serial.println("gpio - manage GPIO settings.");
  Serial.println("ls - list files in the filesystem.");
  Serial.println("touch - create a file.");
  Serial.println("edit - edit a file.");
  Serial.println("cat - read a file.");
  Serial.println("rm - delete a file.");
  Serial.println("date - manage date and time.");
  Serial.println("uname - show os version.");
  Serial.println("uptime - show system uptime.");
  Serial.println("history - show command history.");
  Serial.println("wget - download a file.");
  Serial.println("httpd - start HTTP server to browse files.");
  Serial.println("ps - show running tasks.");
  Serial.println("clear - clear the screen.");
}