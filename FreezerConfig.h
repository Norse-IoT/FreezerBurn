#pragma once
#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <ESP_Async_WebServer.h>
#include <chrono>

#include "./page/page.h" //Webpage for the captive portal

#define magnetPin 21
#define ledPin 2


// FreezerConfig.h
class FreezerConfig {
private:
// has this been initialized yet?
  bool isInitialized;
  bool opened;
  // WiFi
  String eapId;
  String eapUsername;
  String eapPassword;
  // SMS credentials to be added later
  int phoneNumber;
  long timeLimit; // equivalent to unsigned long millis()
  String freezerName;
  std::chrono::system_clock::time_point openedTime;

  //web server for captive setup portal
  AsyncWebServer server;
public: 
  String getId() const;
  String getUsername() const;
  String getPassword() const;
  int getPhoneNumber() const;
  long getTimeLimit() const;
  
  bool fromRequest(AsyncWebServerRequest*);

  void setId(String);
  void setUsername(String);
  void setPassword(String);
  void setPhoneNumber(int);
  void setTimeLimit(long);
  void startTimer();
  void stopTimer();
  void wifiConnect();

  bool getInitialized() const;
  bool getOpened() const;
  bool timeLimitReached() const;

  FreezerConfig(); // default constructor
};