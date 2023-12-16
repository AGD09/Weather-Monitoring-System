#include <Blynk.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include "DHT.h"
#include <Adafruit_BMP280.h>

#define BMP_SCK (13)
#define BMP_MOSI (11)
#define BMP_CS (10)
#define BMP_MISO (12)
#define DHTPIN 2     
#define DHTTYPE DHT11  

#define BLYNK_TEMPLATE_ID "TMPLjSkhPXxu"
#define BLYNK_DEVICE_NAME "Weather"
#define BLYNK_AUTH_TOKEN "eE1PaTUm3vkcaPidgKkEOqI6rVy1TDSz"

#define BLYNK_PRINT Serial

char ssid[]="VNRVJIET WIFI" ;
char pass[]="vnrvjiet@123";
char auth[]="eE1PaTUm3vkcaPidgKkEOqI6rVy1TDSz";


Adafruit_BMP280 bmp; 
DHT dht(DHTPIN, DHTTYPE);
int ldr=A0;
int value=0;
int Val0;
int Val2;int Val3;int Val4;int Val5;

void setup() {
  Serial.begin(9600);
  //Serial.begin(115200);
  dht.begin();
  Serial.println(F("BMP280 test"));
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,    
                  Adafruit_BMP280::SAMPLING_X16,    
                  Adafruit_BMP280::FILTER_X16,      
                  Adafruit_BMP280::STANDBY_MS_500);


   Blynk.begin(auth, ssid, pass);
}


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  void loop(){
  value=analogRead(ldr);
    BLYNK_READ(V0);
    Val0=param.asInt();
   Blynk.virtualWrite(V0, Val0);

BLYNK_READ(V2);
   Val2=param.asInt();
  Blynk.virtualWrite(V2, Val2);

BLYNK_READ(V3);
   Val3=param.asInt();
  Blynk.virtualWrite(V3, Val3);

BLYNK_READ(V4);
   Val4=param.asInt();
  Blynk.virtualWrite(V4, Val4);

BLYNK_READ(V5);
   Val5=param.asInt();
  Blynk.virtualWrite(V5, Val5);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F "));
  Serial.println();
  Serial.print("Light intensity: ");
  Serial.println(value);
  //Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println();
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  //Serial.println();
  Serial.print(F("Atmospheric Pressure = "));
  Serial.print(bmp.readPressure()/100);
  Serial.print(" hPa");
  Serial.println();
  Serial.print(F("Approx Altitude = "));
  Serial.print(bmp.readAltitude(1019.66)); 
  Serial.println(" m");                   
  Serial.println();
  delay(3000);
  
}
