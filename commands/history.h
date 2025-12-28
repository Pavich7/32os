void history(const char* param1, const char* param2, const char* param3) {
  preferences.begin("command_history", false);
  int count = preferences.getInt("count", 0);
  for(int i = 1; i <= count; i++){
    String cmd = preferences.getString(String(i).c_str(), "");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(cmd);
  }
  preferences.end();
}