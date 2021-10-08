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
      float controllerTemperature = roundf(getSystemTemperature() * 100) / 100.0;
    if (controllerTemperature > 75.0) {
      if (activatedSMS)SMS(createMessage(systemID, "High Temperature in Controller"));
    }
}

void checkSystemHumidity() {
    if (activatedSIM7000E)
        float controllerHumidity = roundf(getSystemHumidity() * 100) / 100.0;
    if (controllerHumidity > 75.0) {
      if (activatedSMS)SMS(createMessage(systemID, "High Humidity in Controller"));
    }
}
