#include "FreezerConfig.h"
// FreezerConfig.cpp

// default constructor
FreezerConfig::FreezerConfig() 
  : eapId(""),
    eapUsername(""),
    eapPassword(""),
    phoneNumber(0),
    timeLimit(10000),
    freezerName(""),
    isInitalized(false) {}


void FreezerConfig::fromRequest(AsyncWebServerRequest *request) {
  // process request one parameter at a time. lots of `if (request->hasParameter("field-name"))`...
  
}

void FreezerConfig::wifiConnect()
{
  if (wifirecieved == true && wifiConnecting == false)
  {
    wifiConnecting = true;
    WiFi.begin(eapUsername, eapPassword);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(500); 
    }
    
    Serial.println("Successful connection");
  }
}
// define your getters and setters
// e.g.



bool FreezerConfig::isInitalized() const {
  return isInitalized;
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

