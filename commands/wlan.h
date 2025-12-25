#include <WiFi.h>

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
  }else if(String(param1) == "connect"){
    if (param2 == nullptr || strlen(param2) == 0 || param3 == nullptr || strlen(param3) == 0) {
      Serial.println("Error: incorrect parameter > wlan connect <ssid> <password>");
      return;
    }
    WiFi.disconnect();
    delay(100);
    WiFi.begin(String(param2), String(param3));
    Serial.print("Connecting to WiFi");
    unsigned long previousMillis = millis();
    unsigned long currentMillis = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
      currentMillis = millis();
      if (currentMillis - previousMillis > 10000) {
        previousMillis = currentMillis;
        Serial.println("Connect Timeout");
        WiFi.disconnect();
        return;
      }
    }
    Serial.println();
    Serial.println(WiFi.localIP());
    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());
  }else if(String(param1) == "status"){
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("Status: Not connect");
    }else{
      Serial.println("Status: Connected");
      Serial.println(WiFi.localIP());
      Serial.print("RSSI: ");
      Serial.println(WiFi.RSSI());
    }
  }else if(String(param1) == "disconnect"){
    WiFi.disconnect();
    Serial.println("Disconnected");
  }else{
    Serial.println("Wireless Utility");
    Serial.println("list - List all WiFi and RSSI");
    Serial.println("status - Show WiFi status");
    Serial.println("connect <ssid> <password> - Connect to WiFi");
    Serial.println("disconnect - Disconnect WiFi");
    return;
  }
}