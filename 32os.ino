#include "FS.h"
#include "SPIFFS.h"
#include <nvs_flash.h>
#include <Preferences.h>
#include "system/command.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("32os version ");
  Serial.println(VERSION);
  const char compile_timestamp[] = __DATE__ " " __TIME__;
  Serial.print("Compiled on: ");
  Serial.println(compile_timestamp);
  Serial.print("SDK Version: ");
  Serial.println(esp_get_idf_version());
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("File System Mount Failed!");
  }else{
    Serial.println("File System Mounted.");
  }
  preferences.begin("sys_config", false);
  int cpu_freq = preferences.getInt("cpu_freq", 240);
  preferences.end();
  setCpuFrequencyMhz(cpu_freq);
  Serial.print("CPU Frequency set to ");
  Serial.println(cpu_freq);
  wlan("connect-last", nullptr, nullptr);
  preferences.begin("timezone", false);
  int gmt = preferences.getInt("gmt", 0);
  preferences.end();
  if(gmt == 0){
    Serial.println("No saved timezone found. Using GMT 0.");
  }else{
    Serial.print("Timezone found. GMT ");
    Serial.println(gmt);
  }
  configTime(gmt*3600, 0, "pool.ntp.org");
  while (!Serial);
  Serial.println();
  Serial.println("Welcome to 32os!");
  Serial.println("© 2025 Pavich Komansil. All rights reserved.");
  Serial.println();
  Serial.println("'help' command to show list of commands.");
  Serial.println();
  printPrompt();
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == 3) {
      if (currentTask != NULL) {
        vTaskDelete(currentTask);
        currentTask = NULL;
        Serial.println("^C");
        printPrompt();
      }
      continue;
    }
    if (ch == '\b' || ch == 127) {
      if (inputBuffer.length() > 0) {
        inputBuffer.remove(inputBuffer.length() - 1);
        Serial.print("\b \b");
      }
      continue;
    }
    if (ch == '\n' || ch == '\r') {
      if (currentTask == NULL){
        Serial.println();
        if (inputBuffer.length() > 0) {
          runCommand(inputBuffer.c_str());
          inputBuffer = "";
        }else{
          printPrompt();
        }
      }
      continue;
    }
    if (isPrintable(ch)) {
      inputBuffer += ch;
      Serial.print(ch);
    }
  }
}