#include "time.h"

void date(const char* param1, const char* param2, const char* param3) {
  if(String(param1) == "set"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > date set <gmt>");
        return;
    }
    configTime(atoi(param2)*3600, 0, "pool.ntp.org");
    Serial.println("Timezone set.");
  }else if(String(param1) == "help"){
    Serial.println("Date/Time Utility");
    Serial.println("set <gmt> - set timezone.");
  }else{
    Serial.println("Current Date and Time:");
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    return;
  }
}