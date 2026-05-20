#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>

#include "index_html.h"
#include "wlan_info.h"

// config for DHT
#define DHT_TYPE DHT22
#define DHT_PIN D3

// config for OLED
#define OLED_SCL GPIO5
#define OLED_SDA GPIO4
#define OLED_RESET 0


DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128, 64);

const long interval = 2000;


void setup() {
  dht.begin();

  Serial.begin(115200);
  Serial.println("\nDHT running...\n");
}


void loop() {
  float temperatureC = dht.readTemperature();
  float temperatureF = dht.readTemperature(true);
  float humidity = dht.readHumidity();
  
  float dewPoint = temperatureC - ((100 - humidity) / 5);
  float wetBulb = temperatureC * atan(0.151977 * sqrt(humidity + 8.313659)) + atan(temperatureC + humidity) - atan(humidity - 1.676331) + 0.00391838 * sqrt(pow(humidity, 3)) * atan(0.023101 * humidity) - 4.686035;

  Serial.println("Temperature:  " + (String)temperatureC + " °C ");
  Serial.println("Temperature:  " + (String)temperatureF + " F ");
  Serial.println("Humidity:     " + (String)humidity + " % ");
  Serial.println("Dew Point:    " + (String)dewPoint + " °C ");
  Serial.println("Wet Bulb:     " + (String)wetBulb + " °C ");
  Serial.println();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Temperature:  " + (String)temperatureC + " °C ");
  display.println("Temperature:  " + (String)temperatureF + " F ");
  display.println("Humidity:     " + (String)humidity + " % ");
  display.println("Dew Point:    " + (String)dewPoint + " °C ");
  display.println("Wet Bulb:     " + (String)wetBulb + " °C ");
  display.display();

  delay(interval);
}
