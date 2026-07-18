#pragma once

void hostname(const char* param1, const char* param2, const char* param3) {
  if(String(param1) == "set"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > hostname set <name>");
        return;
    }
    preferences.begin("hostname", false);
    preferences.putString("name", String(param2));
    preferences.end();
    Serial.println("Hostname set.");
  }else if(String(param1) == "help"){
    Serial.println("Hostname Utility");
    Serial.println("set <name> - set hostname.");
  }else{
    preferences.begin("hostname", false);
    String hostname = preferences.getString("name", "32os");
    preferences.end();
    Serial.println(hostname);
    return;
  }
}