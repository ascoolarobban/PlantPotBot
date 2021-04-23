/*People are fake, pizza is real*/

const int RELAY_PIN = 13;
const int incomming = 5;
int counter = 0;
int minute = 60000;
int hour = 60 * minute;


void setup() {
  delay(2000);
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(incomming, INPUT);

}


void loop() {


  if (digitalRead(incomming)) {
    Serial.println("incomming");
    Serial.println(counter);
    counter +=1;
    if (counter <= 3) {
      digitalWrite(RELAY_PIN, HIGH);
      delay(30000);
      digitalWrite(RELAY_PIN, LOW);
    }
    else {
      delay(hour * 5);
      counter = 0;
    }


  }
}
