#include <DHT.h>

#define DHT_TYPE DHT22
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

  delay(interval);
}
