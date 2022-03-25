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

void activateDHT22(){
	      clearLCD();
  lcd.setCursor(0, 0); lcd.print("Activate Air Sensor?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
        DHT_22.begin();
      isDHT22Activated=true;
      break;
    }
  }
}
