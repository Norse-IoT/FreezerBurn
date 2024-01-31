#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "page.h" //Webpage for the captive portal
/*
TODO
-Include twilio library
-Set up messaging
*/

#define magnetPin 21
#define ledPin 2

DNSServer dnsServer;
AsyncWebServer server(80);

byte magnetConnected;
int seconds = 0;
int maxSeconds = 10; 

//Setup stuff here
bool timeRecieved = false;
bool wifirecieved = false; //Has the esp gotten the information needed to connect to wifi? 
bool wifiConnecting = false; //Even more so, is the Wifi being connected/has connected?
int userMinutes = 0;
String minutesInput;
String userName;
String currentNetwork;
String wifiPass;

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
  
      if (request->hasParam("seconds")) { //It's actually minutes; this naming mishap is because of the way I originally wrote the webpage
        inputMessage = request->getParam("seconds")->value();
        inputParam = "seconds";
        minutesInput = inputMessage;
        Serial.println(inputMessage);
        timeRecieved = true;
      }
      
      if (request->hasParam("name"))
      {
        inputMessage = request->getParam("name")->value();
        inputParam = "name";
        userName = inputMessage;
        Serial.print("Hello, ");
        Serial.println(inputMessage);
      }

      if (request->hasParam("network"))
      {
        inputMessage = request->getParam("network")->value();
        inputParam = "network";
        currentNetwork = inputMessage;
        Serial.print("The current preferred network is ");
        Serial.println(currentNetwork);
      }

      if (request->hasParam("netpass"))
      {
        inputMessage = request->getParam("netpass")->value();
        inputParam = "netpass";
        wifiPass = inputMessage;
      }

      if (wifiPass > "" && currentNetwork > " ") wifirecieved = true;
      //This goes at the end of the entire sequence
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
  //Non-web stuff
  pinMode(magnetPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  //Back to web stuff
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Freezer Burn");
  setupServer();
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
}

void wifiConnect()
{
  if (wifirecieved == true && wifiConnecting == false)
  {
    wifiConnecting = true;
    WiFi.begin(currentNetwork, wifiPass);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(500); 
    }

    Serial.println("Successful connection");
  }
}

void loop()
{
  //DNS stuff
  dnsServer.processNextRequest();
  wifiConnect(); //It's probably better to try it through setup but it's not an option here because the wifi nextworks are not defined at first
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
        Serial.print(userName);
        Serial.println(", your freezer or fridge is open. Please close it immediately.");
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
