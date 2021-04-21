#include "DHT.h"
#include "MoistCheck.h"
#include "DhtSensor.h"
DHT dht(DHTPIN, DHTTYPE);
void setup()
{

  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  delay(1000);

}

void loop()
{
  MoistCheck();
 // DhtSensor();

}
