#pragma once

void ps(const char* param1, const char* param2, const char* param3) {
  char buffer[1024];
  Serial.println("Task Name\tStatus\tPrio\tStack\tTaskID\tCore");
  Serial.println("-----------------------------------------------------");
  vTaskList(buffer);
  Serial.println(buffer);
}