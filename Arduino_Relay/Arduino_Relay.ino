/*People are fake, pizza is real*/

const int RELAY_PIN = 13;
const int incomming = 5;



void setup() {
  delay(2000);
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(incomming, INPUT);

}


void loop() {
  
  if(digitalRead(incomming)) {
      digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
      delay(5000);
      digitalWrite(RELAY_PIN, LOW);  // turn off pump 5 seconds
      delay(5000);
      
  }
}
