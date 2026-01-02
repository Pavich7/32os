#include "FS.h"
#include "SPIFFS.h"
#include <nvs_flash.h>
#include <Preferences.h>
#include "system/command.h"
#include "system/history.h"

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
  if (!SPIFFS.begin(true)) {
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
  Serial.println("© 2026 Pavich Komansil. All rights reserved.");
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
        historyIndex = -1;
      }
      continue;
    }
    if (ch == '\n' || ch == '\r') {
      if (currentTask == NULL){
        Serial.println();
        if (inputBuffer.length() > 0) {
          recordHistory(inputBuffer.c_str());
          runCommand(inputBuffer.c_str());
          inputBuffer = "";
          historyIndex = -1;
        }else{
          printPrompt();
        }
      }
      continue;
    }
    if (ch == 27 && currentTask == NULL) {
      while (Serial.available() < 2);
      char ch1 = Serial.read();
      char ch2 = Serial.read();
      if (ch1 == '[') {
        if (ch2 == 'A') {
          inputBuffer = getPrevHistory();
          Serial.print("\r");
          for (int i = 0; i < 80; i++) {
            Serial.print(" ");
          }
          Serial.print("\r");
          printPrompt();
          Serial.print(inputBuffer);
        } else if (ch2 == 'B') {
          inputBuffer = getNextHistory();
          Serial.print("\r");
          for (int i = 0; i < 80; i++) {
            Serial.print(" ");
          }
          Serial.print("\r");
          printPrompt();
          Serial.print(inputBuffer);
        }
      }
      continue;
    }

    if (isPrintable(ch)) {
      historyIndex = -1;
      inputBuffer += ch;
      Serial.print(ch);
    }
  }
}