#include "FS.h"
#include "SPIFFS.h"
#include <EEPROM.h>
#include <Preferences.h>
#include "commands/help.h"
#include "commands/echo.h"
#include "commands/reboot.h"
#include "commands/exit.h"
#include "commands/wlan.h"
#include "commands/system.h"
#include "commands/gpio.h"
#include "commands/ls.h"
#include "commands/touch.h"
#include "commands/cat.h"
#include "commands/rm.h"
#include "commands/date.h"
#include "commands/clear.h"

struct Command {
  const char* name;
  void (*func)(const char*, const char*, const char*);
};

Command commands[] = {
  {"help", help},
  {"echo", echo},
  {"wlan", wlan},
  {"reboot", reboot},
  {"exit", exit},
  {"system", system},
  {"gpio", gpio},
  {"ls", ls},
  {"touch", touch},
  {"cat", cat},
  {"rm", rm},
  {"date", date},
  {"clear", clear},
};

const int commandCount = sizeof(commands) / sizeof(commands[0]);
String inputBuffer = "";

void printPrompt() {
  Serial.print("$ ");
}

void runCommand(const char* input) {
  char buffer[64];
  strncpy(buffer, input, sizeof(buffer));
  buffer[sizeof(buffer)-1] = '\0';
  char* cmd    = strtok(buffer, " ");
  char* param1 = strtok(nullptr, " ");
  char* param2 = strtok(nullptr, " ");
  char* param3 = strtok(nullptr, " ");
  if (!cmd) {
    return;
  }
  for (int i = 0; i < commandCount; i++){
    if (strcmp(commands[i].name, cmd) == 0) {
      commands[i].func(param1, param2, param3);
      return;
    }
  }
  Serial.println("Error: command not found");
}

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS Mount Failed!");
  }
  EEPROM.begin(1);
  int cpu_freq = EEPROM.read(0);
  if(cpu_freq==0 || cpu_freq==255){
    cpu_freq=240;
  }
  setCpuFrequencyMhz(cpu_freq);
  preferences.begin("net_credentials", false);
  String ssid = preferences.getString("ssid", ""); 
  String password = preferences.getString("password", "");
  preferences.end();
  if (ssid == "" || password == ""){
    Serial.println("No saved network credentials found.");
  }else{
    wlan("connect", ssid.c_str(), password.c_str());
  }
  while (!Serial);
  Serial.println();
  Serial.println("Welcome to 32os!");
  Serial.println("Version: 20251225");
  const char compile_timestamp[] = __DATE__ " " __TIME__;
  Serial.print("Compiled on: ");
  Serial.println(compile_timestamp);
  Serial.print("SDK Version: ");
  Serial.println(esp_get_idf_version());
  Serial.println("© 2025 Pavich Komansil. All rights reserved.");
  Serial.println();
  Serial.println("'help' command to show list of commands.");
  Serial.println();
  printPrompt();
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\b' || ch == 127) {
      if (inputBuffer.length() > 0) {
        inputBuffer.remove(inputBuffer.length() - 1);
        Serial.print("\b \b");
      }
      continue;
    }
    if (ch == '\n' || ch == '\r') {
      Serial.println();
      if (inputBuffer.length() > 0) {
        runCommand(inputBuffer.c_str());
        inputBuffer = "";
      }
      printPrompt();
      continue;
    }
    if (isPrintable(ch)) {
      inputBuffer += ch;
      Serial.print(ch);
    }
  }
}
