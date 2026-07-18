#pragma once

void wlan(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: missing parameter");
    return;
  }else if(String(param1) == "list"){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Starting scan...");
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
      Serial.println("No networks found");
    } else {
      Serial.print(n);
      Serial.println(" networks found:");
      for (int i = 0; i < n; i++) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm)");
        delay(10);
      }
    }
  }else if(String(param1) == "internal-connect"){
    WiFi.disconnect();
    delay(100);
    preferences.begin("hostname", false);
    String hostname = preferences.getString("name", "32os");
    preferences.end();
    WiFi.setHostname(hostname.c_str());
    WiFi.begin(String(param2), String(param3));
    Serial.print("Connecting to WiFi");
    unsigned long previousMillis = millis();
    unsigned long currentMillis = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1500);
      currentMillis = millis();
      if (currentMillis - previousMillis > 9000) {
        previousMillis = currentMillis;
        Serial.println("Connect Timeout");
        WiFi.disconnect();
        return;
      }
    }
    Serial.println();
    wlan("status", nullptr, nullptr);
  }else if(String(param1) == "connect-last"){
    preferences.begin("net_credentials", false);
    String ssid = preferences.getString("ssid", "");
    String password = preferences.getString("password", "");
    preferences.end();
    if (ssid == "" || password == ""){
      Serial.println("No saved network credentials found.");
    }else{
      wlan("internal-connect", ssid.c_str(), password.c_str());
    }
  }else if(String(param1) == "connect"){
    //Workaround for connect timeout issue by calling save then connect-last instead of directly connect.
    if (param2 == nullptr || strlen(param2) == 0 || param3 == nullptr || strlen(param3) == 0) {
      Serial.println("Error: incorrect parameter > wlan connect <ssid> <password>");
      return;
    }
    wlan("save", param2, param3);
    wlan("connect-last", nullptr, nullptr);
  }else if(String(param1) == "status"){
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi not connected");
    }else{
      Serial.println("WiFi Connected");
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID()); 
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("Hostname: ");
      Serial.println(WiFi.getHostname());
      Serial.print("RSSI: ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");
    }
  }else if(String(param1) == "disconnect"){
    WiFi.disconnect();
    Serial.println("Disconnected");
  }else if(String(param1) == "forget"){
    WiFi.disconnect();
    preferences.begin("net_credentials", false);
    preferences.putString("ssid", ""); 
    preferences.putString("password", "");
    preferences.end();
    Serial.println("Network credentials forgotten");
  }else if(String(param1) == "save"){
    if (param2 == nullptr || strlen(param2) == 0 || param3 == nullptr || strlen(param3) == 0) {
      Serial.println("Error: incorrect parameter > wlan save <ssid> <password>");
      return;
    }
    preferences.begin("net_credentials", false);
    preferences.putString("ssid", param2); 
    preferences.putString("password", param3);
    preferences.end();
  }else if(String(param1) == "credentials"){
    preferences.begin("net_credentials", false);
    String ssid = preferences.getString("ssid", "");
    String password = preferences.getString("password", "");
    preferences.end();
    if (ssid == "" || password == ""){
      Serial.println("No saved network credentials found.");
    }else{
      Serial.print("SSID: ");
      Serial.println(ssid);
      Serial.print("Password: ");
      Serial.println(password);
    }
  }else{
    Serial.println("Wireless Utility");
    Serial.println("list - List all WiFi and RSSI");
    Serial.println("status - Show WiFi status");
    Serial.println("connect <ssid> <password> - Connect to WiFi");
    Serial.println("connect-last - Connect to last WiFi");
    Serial.println("save - Save WiFi credentials");
    Serial.println("forget - Forget saved WiFi credentials");
    Serial.println("credentials - Show saved WiFi credentials");
    Serial.println("disconnect - Disconnect WiFi");
    return;
  }
}