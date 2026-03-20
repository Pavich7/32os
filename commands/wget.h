#pragma once

void wget(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("wget <url> - download a file.");
    return;
  }
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(param1);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String disposition = http.header("Content-Disposition");
      String fileName = "/download";
      if (disposition.length() > 0) {
        int pos = disposition.indexOf("filename=");
        if (pos != -1) {
          fileName = "/" + disposition.substring(pos + 9);
          fileName.trim();
          fileName.replace("\"", "");
        }
      } else {
        int slashPos = String(param1).lastIndexOf('/');
        if (slashPos != -1) {
          fileName = "/" + String(param1).substring(slashPos + 1);
        }
      }
      Serial.printf("Saving as: %s", fileName.c_str());
      Serial.println();
      File file = SPIFFS.open(fileName, FILE_WRITE);
      if (!file) {
        Serial.println("Failed to open file for writing");
        return;
      }
      WiFiClient* stream = http.getStreamPtr();
      uint8_t buffer[128];
      int len;
      while (http.connected() && (len = stream->readBytes(buffer, sizeof(buffer))) > 0) {
        file.write(buffer, len);
      }
      file.close();
      Serial.println("File saved!");
    } else {
      Serial.printf("HTTP GET failed, code: %d", httpCode);
      Serial.println();
    }
    http.end();
  } else {
    Serial.println("Error: WiFi not connected");
  }
}