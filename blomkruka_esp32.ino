#include <PubSubClient.h>
#include "DHT.h"
//#include "MoistCheck.h"
#include "wifiConnect.h"
int M_Sensor = 34;
int Moisture = 0;
int moistPercent = 0;

int oldStatus = 0;

const int dryValue = 4096;
const int wetValue = 2800;
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
void setStatus(int newStatus) {
  if (oldStatus != newStatus) {
    Serial.println("old: ");
    Serial.println(oldStatus);
    Serial.println("New: ");
    Serial.println(newStatus);
    oldStatus = newStatus;
    Serial.println("AFTER SWITCH");
    Serial.println("old: ");
    Serial.println(oldStatus);
    Serial.println("New: ");
    Serial.println(newStatus);
    delay(5000);



    if (oldStatus == 1) {

      Serial.println("case 1 DRY");
      client.publish(mqttMoist, "DRY");
      delay(500);
      client.publish(mqttMoist, String (moistPercent).c_str(), true);
      delay(5000);
    }
    else if (oldStatus == 2)
    {

      Serial.println("case 2 Moist");
      client.publish(mqttMoist, "MOIST");
      delay(500);
      client.publish(mqttMoist, String (moistPercent).c_str(), true);
      delay(5000);
    }

    else if (oldStatus == 3) {
      Serial.println("case 3 Wet");
      client.publish(mqttMoist, "WET");
      delay(500);
      client.publish(mqttMoist, String (moistPercent).c_str(), true);
    }
  }

}


void loop()
{
  int newStatus = 0;

  Moisture = analogRead(M_Sensor);
  moistPercent = map(Moisture, dryValue, wetValue, 0, 100);

  Serial.println(Moisture);
  delay(1000);
  if (Moisture > 3950)  // for dry soil
  {

    newStatus = 1;
    setStatus(newStatus);
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
    setStatus(newStatus);
    digitalWrite(Relay, LOW);

    Serial.println("MOIST SOIL");
    Serial.print(moistPercent);
    Serial.println("%");
  }

  else
  {
    newStatus = 3;
    setStatus(newStatus);
    digitalWrite(Relay, LOW);
    
    Serial.println("WET");
    Serial.print(moistPercent);
    Serial.println("%");

  }

}
