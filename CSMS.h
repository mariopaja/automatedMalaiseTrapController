/*
  getSoilMoisture() : Reads A3 Pin
                    : Maps A3 value
                    : Return value
*/
int getSoilMoisture() {
  sensorVal = analogRead(A3);
  return map(sensorVal, wet, dry, 100, 0);
}

/*
    checkSoilMoisture   :   checks the soil moisture
                        :   0 & 100 represent the soil moisture value in %
                        :   checks is the sensor is properly operating
*/
bool checkSoilMoisture(int soilMoisture) {
  if (soilMoisture >= 0 && soilMoisture <= 100)return true;
  return false;
}

void activateCSMS(){
    	      clearLCD();
  lcd.setCursor(0, 0); lcd.print("Activate Soil Moist?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
      isCSMSActivated=true;
      break;
    }
  }
}