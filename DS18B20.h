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

void activateDS18B20(){
      clearLCD();
  lcd.setCursor(0, 0); lcd.print("Activate Soil Temp?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
      DS18B20sensor.begin();
      isDS18B20Activated=true;
      break;
    }
  }
}
