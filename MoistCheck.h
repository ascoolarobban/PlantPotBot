void MoistCheck(int Relay) {
  int M_Sensor = 4;
  int Moisture = analogRead(M_Sensor);
  
  
  Serial.println(Moisture);
  delay(1000);
  if (Moisture > 2000)  // for dry soil
  {
    Serial.println ("DRY SOIL");
    digitalWrite(Relay, HIGH);
    delay(4000);
    digitalWrite(Relay, LOW);

  }
  else if (Moisture >= 1700 && Moisture <= 2000) //for Moist Soil
  {
    digitalWrite(Relay, LOW);
    Serial.println("MOIST SOIL");
  }

  else
  {
    digitalWrite(Relay, LOW);
    Serial.println("WET");
  }

}
