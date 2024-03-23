#include "FreezerConfig.h"
// FreezerConfig.cpp
// this is the config logic for a single freezer


// default constructor
FreezerConfig::FreezerConfig() 
  : isInitialized(false), 
    eapId(""),
    eapUsername(""),
    eapPassword(""),
    phoneNumber(0),
    timeLimit(10000),
    freezerName(""), 
    server(80),
    openedTime(), 
    opened(false) {}



// main logic
bool FreezerConfig::fromRequest(AsyncWebServerRequest *request) {
  // process a POST request for data update
  if (request->hasParam("eap-id")) {
    eapId = request->getParam("eap-id")->value();
  } else return false;
  if (request->hasParam("eap-username")) {
    eapUsername = request->getParam("eap-username")->value();
  } else return false;
  if (request->hasParam("eap-password")) {
    eapPassword = request->getParam("eap-password")->value();
  } else return false;
  if (request->hasParam("time-limit")) {
    timeLimit = request->getParam("time-limit")->value().toInt();
  } else return false;
  if (request->hasParam("eap-id")) {
    eapId = request->getParam("eap-id")->value();
  } else return false;
  if (request->hasParam("eap-id")) {
    eapId = request->getParam("eap-id")->value();
  } else return false;

  return true;
}


void FreezerConfig::startTimer() {
  openedTime = std::chrono::system_clock::now();
  opened = true;
}

void FreezerConfig::stopTimer() {
  opened = false;
}

bool FreezerConfig::timeLimitReached() const {
  std::chrono::system_clock::time_point cur_time = std::chrono::system_clock::now();
  std::chrono::system_clock::duration elapsed = (cur_time - openedTime);
  if (elapsed > std::chrono::milliseconds(timeLimit)) {
    return true;
  } else return false;
}


void FreezerConfig::wifiConnect()
{
  WiFi.begin(eapUsername, eapPassword);
  Serial.print("Connecting");
  // will wait for initial user connection for setup
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500); 
  } 
  Serial.println();
  Serial.println("Successful connection");
}


// getters
bool FreezerConfig::getInitialized() const {
  return isInitialized;
}
bool FreezerConfig::getOpened() const {
  return opened;
}
String FreezerConfig::getId() const {
  return eapId;
}
String FreezerConfig::getUsername() const {
  return eapUsername;
}
String FreezerConfig::getPassword() const {
  return eapPassword;
}
int FreezerConfig::getPhoneNumber() const {
  return phoneNumber;
}
long FreezerConfig::getTimeLimit() const {
  return timeLimit;
}


// setters
void FreezerConfig::setId(String id) {
  eapId = id;
}
void FreezerConfig::setPassword(String pass) {
  eapPassword = pass;
}
void FreezerConfig::setPhoneNumber(int num) {
  phoneNumber = num;
}
void FreezerConfig::setTimeLimit(long num) {
  timeLimit = num;
}
void FreezerConfig::setUsername(String name) {
  eapUsername = name;
}