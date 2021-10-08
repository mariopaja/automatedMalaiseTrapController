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

double getSystemTemperature() {
  return bme.getTemperature();
}

double getSystemHumidity() {
  return bme.getHumidity();
}

void checkSystemTemperature() {
  if (activatedSIM7000E)
    if (getSystemTemperature() > double(75)) {
      SMS("System Temperature is too High");
    }
}

void checkSystemHumidity() {
  if (activatedSIM7000E)
    if (getSystemHumidity() > double(75)) {
      SMS("System Humidity is too High");
    }
}