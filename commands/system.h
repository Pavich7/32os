void system(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: missing parameter");
    return;
  }else if(String(param1) == "status"){
    if(String(param2) == "ram"){
      Serial.printf("Total Heap: %u bytes", ESP.getHeapSize());
      Serial.println();
      Serial.printf("Free Heap: %u bytes", ESP.getFreeHeap());
      Serial.println();
    }else if(String(param2) == "cpu"){
      int freq = getCpuFrequencyMhz();
      Serial.print(freq);
      Serial.println(" Mhz");
    }else{
      Serial.println("Error: incorrect parameter > system status <devices>");
      return;
    }
  }else if(String(param1) == "set"){
    if(String(param2) == "cpu"){
      if(param3 == nullptr || strlen(param3) == 0){
        Serial.println("Error: incorrect parameter > system set cpu <value>");
        return;
      }
      EEPROM.write(0, atoi(param3));
      EEPROM.commit();
      Serial.println("Setting will apply on next reboot.");
    }else{
      Serial.println("Error: incorrect parameter > system set <devices> <value>");
      return;
    }
  }else{
    Serial.println("System Utility");
    Serial.println("status <device> - show device status");
    Serial.println("set <device> <value> - set device value");
    return;
  }
}