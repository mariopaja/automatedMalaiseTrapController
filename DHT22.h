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

/*
	checkAirHumidity()	:	check the value of air humidity
						:	the value 100 represents the %
						:	this boolean checks if the sensor is operating properly
*/
bool checkAirHumidity(float airHumidity) {
  if (airHumidity >= 0 && airHumidity <= 100)return true;
  return false;
}
