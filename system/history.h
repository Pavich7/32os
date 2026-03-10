#pragma once

int historyIndex = -1;

void recordHistory(const char* input){
  preferences.begin("command_history", false);
  int count = preferences.getInt("count", 0);
  count++;
  preferences.putInt("count", count);
  preferences.putString(String(count).c_str(), String(input));
  preferences.end();
}

String getHistory(int index) {
  preferences.begin("command_history", true);
  int count = preferences.getInt("count", 0);
  String cmd = "";
  if (index > 0 && index <= count) {
    cmd = preferences.getString(String(index).c_str(), "");
  }
  preferences.end();
  return cmd;
}

String getPrevHistory() {
  preferences.begin("command_history", true);
  int count = preferences.getInt("count", 0);
  preferences.end();
  if (count == 0) return "";
  if (historyIndex == -1) {
    historyIndex = count;
  } else if (historyIndex > 1) {
    historyIndex--;
  }
  return getHistory(historyIndex);
}

String getNextHistory() {
  preferences.begin("command_history", true);
  int count = preferences.getInt("count", 0);
  preferences.end();
  if (count == 0) return "";
  if (historyIndex == -1) {
    return "";
  }
  if (historyIndex < count) {
    historyIndex++;
    return getHistory(historyIndex);
  } else {
    historyIndex = -1;
    return "";
  }
}