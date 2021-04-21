#include <PubSubClient.h>
#include "DHT.h"
//#include "MoistCheck.h"
#include "wifiConnect.h"
int M_Sensor = 34;
int Moisture = analogRead(M_Sensor);

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

void loop()
{


  Serial.println(Moisture);
  delay(1000);
  if (Moisture > 2000)  // for dry soil
  {
    Serial.println ("DRY SOIL");
    client.publish(mqttMoist, "DRY");
    digitalWrite(Relay, HIGH);
    delay(4000);
    digitalWrite(Relay, LOW);

  }
  else if (Moisture >= 1700 && Moisture <= 2000) //for Moist Soil
  {
    digitalWrite(Relay, LOW);
    Serial.println("MOIST SOIL");
    client.publish(mqttMoist, "Moist Soil");
  }

  else
  {
    digitalWrite(Relay, LOW);
    Serial.println("WET");
    client.publish(mqttMoist, "WET");
  }


  //MoistCheck(Relay, mqttMoist);

  //DhtSensor();

}
