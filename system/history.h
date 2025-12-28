void recordHistory(const char* input){
  preferences.begin("command_history", false);
  int count = preferences.getInt("count", 0);
  count++;
  preferences.putInt("count", count);
  preferences.putString(String(count).c_str(), String(input));
  preferences.end();
}