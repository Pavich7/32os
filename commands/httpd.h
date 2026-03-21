#pragma once

WebServer server(80);
TaskHandle_t httpdTaskHandle = NULL;
bool ServerInitFinished = false;

void httpdTask(void* pvParameters) {
  server.on("/", []() {
    String html = "<h1>32os File Browser</h1><ul>";
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
      html += "<li><a href=\"/file?name=" + String(file.name()) + "\">" + String(file.name()) + "</a></li>";
      file = root.openNextFile();
    }
    html += "</ul>";
    server.send(200, "text/html", html);
  });
  server.on("/file", []() {
    if (!server.hasArg("name")) {
      server.send(400, "text/plain", "Missing filename");
      return;
    }
    String filename = server.arg("name");
    if (!filename.startsWith("/")) filename = "/" + filename;
    File file = SPIFFS.open(filename, FILE_READ);
    if (!file) {
      server.send(404, "text/plain", "File not found");
      return;
    }
    String contentType = "application/octet-stream";
    String header = "attachment; filename=\"" + String(file.name()) + "\"";
    server.sendHeader("Content-Disposition", header);
    server.streamFile(file, contentType);
    file.close();
  });
  server.begin();
  ServerInitFinished = true;
  for (;;) {
    server.handleClient();
    delay(10);
  }
}

void httpd(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: missing parameter");
    return;
  }else if(String(param1) == "start"){
    if (httpdTaskHandle != NULL) {
      Serial.println("Server is already running.");
      return;
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Error: Connect to WiFi before starting the server.");
      return;
    }
    Serial.println("Starting HTTP server...");
    ServerInitFinished = false;
    xTaskCreate(httpdTask, "httpdTask", 8192, NULL, 1, &httpdTaskHandle);
    while(!ServerInitFinished) {
      delay(10);
    }
    Serial.println("Server started.");
    Serial.println("Access the file browser at http://" + WiFi.localIP().toString());
  }else if(String(param1) == "stop"){
    if (httpdTaskHandle == NULL) {
      Serial.println("Server is not running.");
      return;
    }
    vTaskDelete(httpdTaskHandle);
    httpdTaskHandle = NULL;
    Serial.println("Server stopped.");
  }else{
    Serial.println("32os HTTP Server File Browser");
    Serial.println("Usage: httpd <start|stop> - Start/stop the server");
  }
}