/*
  getAirHumidity() : Return Relative Air Humidity
*/
float getAirHumidity() {
  return DHT_22.readHumidity();
}


/*
  getAirTemperature() : Return Air Temperature
*/
float getAirTemperature() {
  return DHT_22.readTemperature();
}
bool checkAirHumidity() {
  if (getAirHumidity() >= 0 && getAirHumidity() <= 100)return true;
  return false;
}
