#include <PubSubClient.h>
#include "DHT.h"
//#include "MoistCheck.h"
#include "wifiConnect.h"
int M_Sensor = 34;
int Moisture = 0;
int moistPercent = 0;
int newStatus;
int oldStatus;

const int dryValue = 4096;
const int wetValue = 2865;
WiFiClient espClient;
PubSubClient client(espClient);

#define mqttMoist "lucifer/moist"
#define mqtt_server "10.0.1.19"




const int Relay = 13;



void setup()
{

  pinMode(Relay, OUTPUT);


  Serial.begin(115200);
  wifiBegin();
  client.setServer(mqtt_server, 1883);
  client.connect("blomkruka");
  delay(1000);


}
void setStatus(int newStatus, int oldStatus) {
  if (oldStatus != newStatus) {
    oldStatus = newStatus;
    switch (newStatus) {
      case 1:
        client.publish(mqttMoist, "DRY");
        client.publish(mqttMoist, String (moistPercent).c_str(), true);
        break;
      case 2:
        client.publish(mqttMoist, "MOIST");
        client.publish(mqttMoist, String (moistPercent).c_str(), true);
        break;

      case 3:
        client.publish(mqttMoist, "WET");
        client.publish(mqttMoist, String (moistPercent).c_str(), true);
        break;
    }

  }
}

  void loop()
  {

    Moisture = analogRead(M_Sensor);
    moistPercent = map(Moisture, dryValue, wetValue, 0, 100);

    Serial.println(Moisture);
    delay(1000);
    if (Moisture > 3950)  // for dry soil
    {

      newStatus = 1;
      setStatus(newStatus,oldStatus);
      Serial.println ("DRY SOIL");
      Serial.print(moistPercent);
      Serial.println("%");

      digitalWrite(Relay, HIGH);
      delay(4000);
      client.publish(mqttMoist, "watered");
      digitalWrite(Relay, LOW);

    }
    else if (Moisture >= 3000 && Moisture <= 3950) //for Moist Soil
    {
      newStatus = 2;
      setStatus(newStatus,oldStatus);
      digitalWrite(Relay, LOW);

      Serial.println("MOIST SOIL");
      Serial.print(moistPercent);
      Serial.println("%");

      client.publish(mqttMoist, "Moist Soil");
      client.publish(mqttMoist, String (moistPercent).c_str(), true);
    }

    else
    {
      newStatus = 3;
      setStatus(newStatus,oldStatus);
      digitalWrite(Relay, LOW);

      Serial.println("WET");
      Serial.print(moistPercent);
      Serial.println("%");

    }

  }
