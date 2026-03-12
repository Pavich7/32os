#pragma once

#define VERSION 20260312

#include <Arduino.h>
#include <time.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <nvs_flash.h>
#include <Preferences.h>

extern Preferences preferences;

#include "system/history.h"
#include "system/filesystem.h"

#include "commands/help.h"
#include "commands/echo.h"
#include "commands/reboot.h"
#include "commands/exit.h"
#include "commands/wlan.h"
#include "commands/system.h"
#include "commands/gpio.h"
#include "commands/ls.h"
#include "commands/touch.h"
#include "commands/edit.h"
#include "commands/cat.h"
#include "commands/rm.h"
#include "commands/date.h"
#include "commands/uname.h"
#include "commands/uptime.h"
#include "commands/history.h"
#include "commands/clear.h"

#include "system/command.h"
