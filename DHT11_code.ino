#include <Blynk.h>

#include <WiFi.h>
#include <WiFiClient.h>


#define BLYNK_PRINT Serial
#include<BlynkSimpleESP32.h>


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"
#define DHTPIN 4    
#define DHTTYPE DHT11  

#define BLYNK_TEMPLATE_ID "TMPLjSkhPXxu"
#define BLYNK_DEVICE_NAME "sample"
//#define BLYNK_AUTH_TOKEN "eE1PaTUm3vkcaPidgKkEOqI6rVy1TDSz"

char ssid[]="VNRVJIET_WIFI";
char pass[]="vnrvjiet@123";
char auth[]="eE1PaTUm3vkcaPidgKkEOqI6rVy1TDSz";

DHT dht(DHTPIN, DHTTYPE);


BLYNK_WRITE(V0){
  if(param.asInt()==1){
    digitalWrite(4,HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  dht.begin();
  Blynk.begin(auth,ssid,pass);
}

void loop() {
  
  

  
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();
  
  float f = dht.readTemperature(true);

  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  
  float hif = dht.computeHeatIndex(f, h);
 
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  delay(2000);
  Blynk.run();
}
