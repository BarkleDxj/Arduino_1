//SimpleDemo
#include <string.h>
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
SSD1306Wire display(0x3c, 2, 14); 
#define DEMO_DURATION 3000

//DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 5     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

//    ***  typedef void (*Demo)(void);


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  
  
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  char Temp[30] = "Temperature: ";
  char Hum[30] = "Humidity: ";

  //itoa((int)event.temperature, Temp, 10);
  
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  //display message
  if (isnan(event.temperature)) {
    display.drawString(0, 10, "Error reading temperature!");
    //Serial.println(F("Error reading temperature!"));
  }
  else {
    char Temp1[10];
    sprintf(Temp1, "%.2f", event.temperature);
    strcat(Temp, Temp1);
    strcat(Temp, "°C");
    display.drawString(0, 10, Temp);
    /*
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    */
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  //itoa((int)event.relative_humidity, Hum, 10);
  
  if (isnan(event.relative_humidity)) {
    display.drawString(0, 20, "Error reading humidity!");
    //Serial.println(F("Error reading humidity!"));
  }
  else {
    char Hum1[10];
    sprintf(Hum1, "%.2f", event.relative_humidity);
    strcat(Hum, Hum1);
    strcat(Hum, "%");
    display.drawString(0, 20, Hum);
    
 
    /*
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    */
  }
  display.display();
  delay(100);

}
