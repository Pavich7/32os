#pragma once

void gpio(const char* param1, const char* param2, const char* param3) {
  if (param1 == nullptr || strlen(param1) == 0) {
    Serial.println("Error: missing parameter");
    return;
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
  }else if(String(param1) == "get"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio get <pin>");
        return;
    }
    pinMode(atoi(param2), INPUT);
    Serial.print("Get pin: ");
    Serial.print(atoi(param2));
    Serial.print(" value: ");
    Serial.println(digitalRead(atoi(param2)));
  }else if(String(param1) == "get-pullup"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio get-pullup <pin>");
        return;
    }
    pinMode(atoi(param2), INPUT_PULLUP);
    Serial.print("Get pull-up pin: ");
    Serial.print(atoi(param2));
    Serial.print(" value: ");
    Serial.println(digitalRead(atoi(param2)));
  }else if(String(param1) == "get-analog"){
    if(param2 == nullptr || strlen(param2) == 0){
        Serial.println("Error: incorrect parameter > gpio get-analog <pin>");
        return;
    }
    pinMode(atoi(param2), INPUT);
    Serial.print("Get analog pin: ");
    Serial.print(atoi(param2));
    Serial.print(" value: ");
    Serial.println(analogRead(atoi(param2)));
  }else{
    Serial.println("GPIO Utility");
    Serial.println("set <pin> <value> - set pin value.");
    Serial.println("set-analog <pin> <value> - set pin analog value.");
    Serial.println("get <pin> - get pin value.");
    Serial.println("get-pullup <pin> - get pin value with pull-up resistor.");
    Serial.println("get-analog <pin> - get analog pin value.");
    return;
  }
}