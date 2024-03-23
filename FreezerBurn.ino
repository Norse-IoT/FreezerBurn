
#include "FreezerConfig.h"

/*
  Required Libraries:
    AsyncTCP by dvarrell 
      LINK https://github.com/dvarrel/AsyncTCP

    ESP_Async_WebServer by me_no_dev 
      LINK https://github.com/mathieucarbou/ESPAsyncWebServer



  I work on the project in a PlatformIO project in VSCode. 
  Source directory of the project is wrapped by another directory. 
  In outer dir, there is src (the project) and lib (with 2 more named dirs for libraries mentioned)
  and a platformio.ini file.

  with the PlatformIO extension installed, it is relatively easy to repeat these project settings for development.

  the platformio.ini file will automatically create the required dependencies for the project if configured correctly
*/

bool wifiConnected = false;

DNSServer dnsServer;
AsyncWebServer server(80);

// create the config object
FreezerConfig config = FreezerConfig();

//Code that I didn't copy paste
class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}
    bool canHandle(AsyncWebServerRequest *request)
    {
        request->addInterestingHeader("ANY");
        return true;
    }
    void handleRequest(AsyncWebServerRequest *request)
    {
        request->send_P(200, "text/html", index_html);
    }
};

void setupServer(){

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html); 
      Serial.println("Client Connected");
  });
    
  server.on("/configure", HTTP_POST, [] (AsyncWebServerRequest *request) {
    if (config.fromRequest(request)) {
      Serial.println("Config Updated Successfully");
      request->send(200, "text/html", "The values were updated successfully<br><a href=\"/\">Return to Home Page</a>");
    } else {
      Serial.println("Config not updated successfully, something went wrong.");
      request->send(400, "text/html", "The values were not updated successfully <br><a href=\"/\">Return to Home Page</a>");
    }
  });
}



void setup()
{
  Serial.begin(9600);
  //Non-web stuff
  pinMode(magnetPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  
  //Back to web stuff
  // Create captive web portal for initial connection
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Freezer Burn");
  setupServer();
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
}


void loop()
{
  if (wifiConnected) {
    config.wifiConnect();
    wifiConnected = true;
  }

  if (digitalRead(magnetPin) == LOW) // then the door is open
  {
    digitalWrite(ledPin, HIGH);
    if(config.getOpened()) {
      if(config.timeLimitReached()) {
        Serial.print(config.getUsername());
        Serial.println(", your freezer or fridge is open. Please close it immediately.");
      }
    } else { // it is open but the timer has not started yet
            // will set config.opened after starting the timer
      config.startTimer();
    }
  } else {
    if(config.getOpened()) { // if it was open before it is closed now
      config.stopTimer(); // so stop the timer 
    }
    digitalWrite(ledPin, LOW);
  }


  dnsServer.processNextRequest();
  delay(1000);
}
