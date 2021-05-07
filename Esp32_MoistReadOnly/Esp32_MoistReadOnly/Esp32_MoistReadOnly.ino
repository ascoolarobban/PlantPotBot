#include <PubSubClient.h>
#include "DHT.h"
#include "wifiConnect.h"
int M_Sensor = 34;
int Moisture = 0;
int moistPercent = 0;
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60*5  /* Time ESP32 will go to sleep (in seconds) */


const int dryValue = 4096;
const int wetValue = 2800;
WiFiClient espClient;
PubSubClient client(espClient);

#define mqttMoist "lucifer/moist"
#define mqtt_server "10.0.1.19"


int newValue = 0;
int oldValue = 0;



void setup() {

  Serial.begin(115200);
  wifiBegin();
  client.setServer(mqtt_server, 1883);
  client.connect("blomkruka");
  Moisture = analogRead(M_Sensor);
  moistPercent = map(Moisture, dryValue, wetValue, 0, 100);

  client.publish(mqttMoist, String (moistPercent).c_str(), true);


  delay(1000);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");


  //ESP.deepSleep(0.2 * 60e6);
  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void loop() {

}
