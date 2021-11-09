#define BLYNK_PRINT SERIAL
#define DHTPIN 14
#define DHTTYPE DHT11
#include <DHT.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "VUpurGm8SRnQvefmrptw5XndVH3ZGr-F";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)) {
    Serial.println("Failed to read temp and humidity");
    return;
  }

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();
  timer.run();
}
