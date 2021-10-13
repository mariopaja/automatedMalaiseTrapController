/*
  getSoilTemperature() : Request Data
                       : Return °C Temperature
                       : To return Temperature in Fahrenheit replace getTempCByIndex(0) with toFahrenheit(Celcius)
*/
double getSoilTemperature() {
  DS18B20sensor.requestTemperatures();
  return DS18B20sensor.getTempCByIndex(0);
}


/*
    checkSoilTemperature()  :   checks the soil temperature value  
                            :   THIS VALUE IS IN °C
                            :   THIS VALUE SHOULD BE CHANGED AND SET BY THE BIOLOGIST
*/
bool checkSoilTemperature(float soilTemperature) {
  if (soilTemperature >= -10.0 && soilTemperature <= 60.0)return true;
  return false;
}
