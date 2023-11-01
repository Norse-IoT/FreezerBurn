#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <stdio.h> //We're taking a wild shot in the dark here but we'll see if this works

#define magnetPin 21
#define ledPin 2

DNSServer dnsServer;
AsyncWebServer server(80);

byte magnetConnected;
int seconds = 0;
int maxSeconds = 10; 

//Setup stuff here
bool timeRecieved = false;
int userMinutes = 0;
String minutesInput;

//There needs to be a more flexible, portable way to do this
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Captive Portal Demo</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h3>Captive Portal Demo</h3>
  <br><br>
  <form action="/get">
    <br>
    Max amount of minutes: <input type="text" name="seconds">
    <br>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

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
    
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      String inputParam;
  
      if (request->hasParam("seconds")) {
        inputMessage = request->getParam("seconds")->value();
        inputParam = "seconds";
        minutesInput = inputMessage;
        Serial.println(inputMessage);
        timeRecieved = true;
      }
      request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>");
  });
}

//And now it's honesty hour again
void secondsInc()
{
  seconds ++;
  Serial.println(seconds);
}

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Freezer Burn");
  setupServer();
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
  pinMode(magnetPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //DNS stuff
  dnsServer.processNextRequest();
  if (timeRecieved == true)
  {
    userMinutes = minutesInput.toInt(); //String to number conversion
    maxSeconds = (userMinutes * 60);
  }
  //And now my stuff
  magnetConnected = digitalRead(magnetPin);

  if (magnetConnected == LOW)
  {
    if (seconds < maxSeconds)
    {
      secondsInc();

      if (seconds == maxSeconds)
      {
        digitalWrite(ledPin, HIGH);
        //And then this is where other stuff would happen
      }
    }
  }
  else
  {
    seconds = 0;
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}
