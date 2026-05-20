#include <DHT.h>

#define DHT_TYPE DHT11
#define DHT_PIN D1

DHT dht(DHT_PIN, DHT_TYPE);

const long interval = 2000;

void setup() {
  dht.begin();

  Serial.begin(115200);
  delay(500);
  Serial.println("\nDHT running...\n");
}

void loop() {
  float temperatureC = dht.readTemperature(true);
  float temperatureF = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println("Temperatur:       " + (String)temperatureC + " °C ");
  Serial.println("Temperatur:       " + (String)temperatureF + " F ");
  Serial.println("Luftfeuchtigkeit: " + (String)humidity + " % ");

  delay(interval);
}
