#include <WiFi.h>
 
const char* ssid     = "Robin's Wi-Fi Network"; // ESP32 and ESP8266 uses 2.4GHZ wifi only
const char* password = "Batman123";
   
void wifiBegin() {
  
  // begin Wifi connect
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  delay(2000);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}
