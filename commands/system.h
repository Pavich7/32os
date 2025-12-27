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
      preferences.begin("sys_config", false);
      preferences.putInt("cpu_freq", atoi(param3));
      preferences.end();
      Serial.println("Setting will apply on next reboot.");
    }else{
      Serial.println("Error: incorrect parameter > system set <devices> <value>");
      return;
    }
  }else if(String(param1) == "erase"){
    Serial.println("Erasing File System...");
    if(SPIFFS.format()){
      Serial.println("File system formatted!");
    }else{
      Serial.println("File system format failed!");
    }
    Serial.println("Erasing Preferences...");
    esp_err_t err = nvs_flash_erase();
    if (err == ESP_OK) {
      Serial.println("Preferences erased!");
    } else {
      Serial.printf("Error erasing Preferences: %s\n", esp_err_to_name(err));
    }
    err = nvs_flash_init();
    if (err == ESP_OK) {
      Serial.println("Preferences initialized!");
    } else {
      Serial.printf("Error initializing Preferences: %s\n", esp_err_to_name(err));
    }
    Serial.println("Preferences cleared!");
    Serial.println("Rebooting...");
    delay(1000);
    ESP.restart();
  }else{
    Serial.println("System Utility");
    Serial.println("status <device> - show device status");
    Serial.println("set <device> <value> - set device value");
    Serial.println("erase - erase all data");
    return;
  }
}