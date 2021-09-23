/*
  getSoilTemperature() : Request Data
                       : Return °C Temperature
                       : To return Temperature in Fahrenheit replace getTempCByIndex(0) with toFahrenheit(Celcius)
*/
double getSoilTemperature() {
  DS18B20sensor.requestTemperatures();
  return DS18B20sensor.getTempCByIndex(0);
}

bool checkSoilTemperature() {
  if (getSoilTemperature() >= -10.0 || getSoilTemperature() <= 60.0)return true;
  return false;
}
