#pragma once

WebServer server(80);

void httpd(const char* param1, const char* param2, const char* param3) {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Starting HTTP server...");
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
    Serial.println("HTTP server started.");
    Serial.println("Access the server at http://" + WiFi.localIP().toString());
    while (true) {
      server.handleClient();
      delay(10);
    }
  } else {
    Serial.println("Error: WiFi not connected");
  }
}