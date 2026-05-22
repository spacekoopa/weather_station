/*
Necessary Libraries:

Adafruit SSD1306
DHT sensor library
Adafruit Unified Sensor
+ the dependencies of these libraries

*/


#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_Sensor.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>

#include "index_html.h"
#include "wlan_info.h"


// config for web interface
#define AP_MODE                     // comment for station mode

const char* ssid = wlan_ssid;        // WIFI SSID for station mode
const char* psk  = wlan_psk;    // WIFI PSK

const char* ap_ssid = wlan_ap_ssid;  // WIFI SSID for AP mode
const char* ap_psk  = wlan_ap_psk; // WIFI PSK

ESP8266WebServer server(80);        // server port

// config for DHT
#define DHT_TYPE DHT22
#define DHT_PIN D3

// config for OLED
#define OLED_SCL GPIO5
#define OLED_SDA GPIO4
#define OLED_RESET 0

// config for LDR
#define LDR A0


DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128, 64);

const long interval = 2000;

unsigned long lastUpdate = 0;


// Global variables for sensor data
float temperatureC;
float temperatureF;
float humidity;
  
float dewPoint;
float wetBulb;

int light;


void setup() {
  // Setup DHT
  dht.begin();

  // Setup Serial Monitor
  Serial.begin(115200);
  Serial.println("\nDHT running...\n");

  // Setup OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();


  #ifdef AP_MODE
    WiFi.mode(WIFI_AP);      // access point mode
    WiFi.softAP(ap_ssid, ap_psk);
    delay(500);           
    Serial.print("IP address ");  // server IP Address
    Serial.println(WiFi.softAPIP());
  #endif

  #ifndef AP_MODE
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, psk);
    // wait for AP association
    Serial.println("Waiting for association...");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Associated with ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  // set event handler
  server.on("/", process_Index);
  server.on("/data", process_Data);
  server.onNotFound(handleNotFound);
 
  server.begin();       // start server
  Serial.println("HTTP Server started");
}


void loop() {
  server.handleClient();

  if ((millis() - lastUpdate >= interval)) {

    lastUpdate = millis();

  
    // get data
    readSensorData();

    // data to serial monitor
    Serial.print("IP address: ");
    #ifdef AP_MODE
      Serial.println(WiFi.softAPIP());
    #endif
    #ifndef AP_MODE
      Serial.println(WiFi.localIP());
    #endif
    Serial.println();

    Serial.println("Temperature:  " + (String)temperatureC + " °C ");
    Serial.println("Temperature:  " + (String)temperatureF + " F ");
    Serial.println("Humidity:     " + (String)humidity + " % ");
    Serial.println("Dew Point:    " + (String)dewPoint + " °C ");
    Serial.println("Wet Bulb:     " + (String)wetBulb + " °C ");
    Serial.print("Light:        ");
    if (light < 1024)
    {
      Serial.print(light);
    }
    else
    {
      Serial.print("Overflow");
    }

    Serial.println();
    Serial.println();
    Serial.println();

    
    // data to oled
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.clearDisplay();

    display.println(" ~ Current Weather ~");

    display.println("Temperature: " + (String)temperatureC + " C");
    int tempWidth = (int)(((temperatureC - (-5)) / (40 - (-5))) * 128);
    tempWidth = min(128, max(0, tempWidth));
    display.fillRect(0, 16, tempWidth, 6, WHITE);

    display.setCursor(0, 24);
    display.println("Humidity:    " + (String)humidity + " %");
    int humWidth = (int)((humidity / 100.0) * 128);
    display.fillRect(0, 32, humWidth, 6, WHITE);
    
    display.setCursor(0, 40);
    display.println("Light:       " + (String)light);
    int lightWidth = (int)((light / 1024.0) * 128);
    display.fillRect(0, 48, lightWidth, 6, WHITE);

    display.setCursor(0, 56);
    display.println(" Have a nice day :3");

    display.display();
  
  }
}


void readSensorData() {
  temperatureC = dht.readTemperature();
  temperatureF = dht.readTemperature(true);
  humidity = dht.readHumidity();
  
  dewPoint = temperatureC - ((100 - humidity) / 5);
  wetBulb = temperatureC * atan(0.151977 * sqrt(humidity + 8.313659)) + atan(temperatureC + humidity) - atan(humidity - 1.676331) + 0.00391838 * sqrt(pow(humidity, 3)) * atan(0.023101 * humidity) - 4.686035;

  light = analogRead(LDR);
}


void process_Index() {
  Serial.println("send index.html");
  server.send(200, "text/html", indexHTML); 
}


void process_Data() {
  // create JSON
  String jsonData = "{\"temperatureC\":" + String(temperatureC, 2) + "," +
                     "\"temperatureF\":" + String(temperatureF, 2) + "," +
                     "\"humidity\":" + String(humidity, 2) + "," +
                     "\"dewPoint\":" + String(dewPoint, 2) + "," +
                     "\"wetBulb\":" + String(wetBulb, 2) + "," +
                     "\"light\":" + String(light) + "}";
  
  // data to website
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json", jsonData);
}


void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found");    // send HTTP status 404 (Not Found)
}
