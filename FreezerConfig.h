#pragma once
#include <DNSServer.h>
#include <WiFi.h>
#include <ESP_Async_WebServer.h>

#include "./page/page.h" //Webpage for the captive portal
// FreezerConfig.h
class FreezerConfig {
private:
// has this been initalized yet?
  bool isInitalized;
  // WiFi
  String eapId;
  String eapUsername;
  String eapPassword;
  // SMS credentials to be added later
  int phoneNumber;
  long timeLimit; // equivalent to unsigned long millis()
  String freezerName;
public: 
  bool isInitialized();
  String getId();
  String getUsername();
  String getPassword();
  int getPhoneNumber();
  long getTimeLimit();
  
  void fromRequest(AsyncWebServerRequest*);

  void setId(String);
  void setUsername(String);
  void setPassword(String);
  void setPhoneNumber(int);
  void setTimeLimit(long);
  void wifiConnect();

  FreezerConfig(); // default constructor
};