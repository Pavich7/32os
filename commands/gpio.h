void gpio(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: missing parameter");
    return;
  }else if(String(param1) == "status"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio status <pin>");
        return;
    }
    Serial.print("GPIO Status: ");
    Serial.println(digitalRead(atoi(param2)));
  }else if(String(param1) == "set"){
    if(param3 == nullptr || strlen(param3) == 0 || param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio set <pin> <value>");
        return;
    }
    pinMode(atoi(param2), OUTPUT);
    digitalWrite(atoi(param2), atoi(param3));
    Serial.print("Set pin: ");
    Serial.print(atoi(param2));
    Serial.print(" to value: ");
    Serial.println(atoi(param3));
  }else if(String(param1) == "set-analog"){
    if(param3 == nullptr || strlen(param3) == 0 || param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio set-analog <pin> <value>");
        return;
    }
    pinMode(atoi(param2), OUTPUT);
    analogWrite(atoi(param2), atoi(param3));
    Serial.print("Set pin: ");
    Serial.print(atoi(param2));
    Serial.print(" to value: ");
    Serial.println(atoi(param3));
  }else{
    Serial.println("GPIO Utility");
    Serial.println("status <pin> - show pin status. (not support analog)");
    Serial.println("set <pin> <value> - set pin value.");
    Serial.println("set-analog <pin> <value> - set pin analog value.");
    return;
  }
}