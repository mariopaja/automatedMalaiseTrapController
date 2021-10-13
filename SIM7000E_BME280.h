/*
    initBME()   :   initiliazes BME280 air sensor that is located in the sim7000e module
*/
void initBME() {
  bme.reset();
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Init. BME280");
  while (bme.begin() != BME::eStatusOK) {
    lcd.setCursor(0, 2); lcd.print("Failed");
    delay(2000);
  }
  lcd.setCursor(0, 2); lcd.print("OK");
  delay(5000);
}


/*
    getSystemTemperature()  :   return controller temperature
*/
double getSystemTemperature() {
  return bme.getTemperature();
}


/*
    getSystemHumidity() :   return controller humidity
*/
double getSystemHumidity() {
  return bme.getHumidity();
}

/*
    checkSystemTemperature()    :   checks the optimal temperature of the controller
                                :   sends SMS to the user 
                                :   NEEDS TO BE SAVED IN THE LOG FILE
*/
void checkSystemTemperature() {
  if (activatedSIM7000E) {
    float controllerTemperature = roundf(getSystemTemperature() * 100) / 100.0;
    if (controllerTemperature > 75.0) {
      if (activatedSMS)SMS(createMessage(systemID, "High Temperature in Controller"));
    }
  }
}

/*
    checkSystemHumodoty()   :   checks the optimal humidity of the controller
                            :   sends SMS to the user
                            :   NEEDS TO BE SAVED IN THE LOG FILE
*/
void checkSystemHumidity() {
  if (activatedSIM7000E) {
    float controllerHumidity = roundf(getSystemHumidity() * 100) / 100.0;
    if (controllerHumidity > 75.0) {
      if (activatedSMS)SMS(createMessage(systemID, "High Humidity in Controller"));
    }
  }
}
