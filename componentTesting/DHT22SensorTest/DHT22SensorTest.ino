#define SERIAL_BAUD    115200

#include <DHTesp.h>



#define DHTTYPE    DHT22 // DHT11, DHT22, DHT21
#define DHT_PIN    4
DHTesp dht;

void setup() {
  Serial.begin(SERIAL_BAUD);

  pinMode(LED_BUILTIN, OUTPUT);

  dht.setup(DHT_PIN, DHTesp::DHTTYPE);
}

void loop() {
  
    TempAndHumidity measurements = dht.getTempAndHumidity();    

    if (isnan(measurements.humidity) || isnan(measurements.temperature)) {
      Serial.println("**Failed to read DHT sensor!**");
    } else {
      Serial.print(measurements.temperature);
      Serial.print("c / ");
      Serial.print(measurements.humidity);
      Serial.println("%).");
    }
    delay(1000);
  }



void blinkLED(int numberOfFlashes, int durationOn, int durationOff) {
  for(int i = 0; i < numberOfFlashes; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(durationOn);
    digitalWrite(LED_BUILTIN, LOW);
    delay(durationOff);
  }
}