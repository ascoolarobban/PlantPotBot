#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

void DhtSensor() {
  DHT dht(DHTPIN, DHTTYPE);
  Serial.println("Dht");
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();



  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C ");


}
