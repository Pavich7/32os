#include "filesystem/fs.h"

void ls(const char* param1, const char* param2, const char* param3) {
  listDir(SPIFFS, "/", 0);
}