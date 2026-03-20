#pragma once

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
  {"edit", edit},
  {"cat", cat},
  {"rm", rm},
  {"date", date},
  {"uname", uname},
  {"uptime", uptime},
  {"history", history},
  {"clear", clear},
  {"wget", wget},
  {"httpd", httpd},
};

const int commandCount = sizeof(commands) / sizeof(commands[0]);
String inputBuffer = "";
TaskHandle_t currentTask = NULL;

void printPrompt() {
  Serial.print("$ ");
}

struct TaskArgs {
  void (*func)(const char*, const char*, const char*);
  const char* p1;
  const char* p2;
  const char* p3;
};

void commandTask(void* pvParameters) {
  TaskArgs* args = (TaskArgs*) pvParameters;
  args->func(args->p1, args->p2, args->p3);
  if (args->p1) free((void*)args->p1);
  if (args->p2) free((void*)args->p2);
  if (args->p3) free((void*)args->p3);
  delete args;
  currentTask = NULL;
  printPrompt();
  vTaskDelete(NULL);
}

static char* allocCopy(const char* src) {
  if (!src) return nullptr;
  size_t len = strlen(src) + 1;
  char* dst = (char*)malloc(len);
  if (dst) memcpy(dst, src, len);
  return dst;
}

void runCommand(const char* input) {
  char buffer[64];
  strncpy(buffer, input, sizeof(buffer));
  buffer[sizeof(buffer)-1] = '\0';
  char* tokens[4] = {nullptr, nullptr, nullptr, nullptr};
  int tokenCount = 0;
  char* p = buffer;
  while (*p && tokenCount < 4) {
    while (*p == ' ') p++;
    if (!*p) break;
    if (*p == '"') {
      p++;
      tokens[tokenCount++] = p;
      while (*p && *p != '"') p++;
      if (*p == '"') {
        *p = '\0';
        p++;
      }
    } else {
      tokens[tokenCount++] = p;
      while (*p && *p != ' ') p++;
      if (*p == ' ') {
        *p = '\0';
        p++;
      }
    }
  }
  char* cmd    = tokens[0];
  char* param1 = tokens[1];
  char* param2 = tokens[2];
  char* param3 = tokens[3];
  if (!cmd) return;
  for (int i = 0; i < commandCount; i++){
    if (strcmp(commands[i].name, cmd) == 0) {
      TaskArgs* args = new TaskArgs{commands[i].func, allocCopy(param1), allocCopy(param2), allocCopy(param3)};
      BaseType_t res = xTaskCreate(commandTask,cmd,4096,args,1,&currentTask);
      if (res != pdPASS) {
        Serial.println("Error: failed to create task");
        if (args->p1) free((void*)args->p1);
        if (args->p2) free((void*)args->p2);
        if (args->p3) free((void*)args->p3);
        delete args;
        printPrompt();
      }
      return;
    }
  }
  Serial.println("Error: command not found");
  printPrompt();
}