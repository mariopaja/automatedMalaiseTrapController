/*
  getSoilMoisture() : Reads A3 Pin
                    : Maps A3 value
                    : Return value
*/
int getSoilMoisture() {
  sensorVal = analogRead(A3);
  return map(sensorVal, wet, dry, 100, 0);
}

bool checkSoilMoisture() {
  if (getSoilMoisture() >= 0 && getSoilMoisture() <= 100)return true;
  return false;
}
