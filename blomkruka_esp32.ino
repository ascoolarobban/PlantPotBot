
#include "MoistCheck.h"
const int Relay = 13;

void setup()
{
  pinMode(Relay, OUTPUT);

  Serial.begin(115200);
  delay(1000);


}

void loop()
{
  MoistCheck(Relay);

  // DhtSensor();

}
