void infoMenu() {
  refreshLCD();
  printMainMenu();
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(8, 3); lcd.print("Info");
  lcd.setCursor(19, 3); lcd.print(" ");
  menuPressedLeft();
  //menuPressedRight();
  if (digitalRead(sel) == LOW && backlitStatus == true) {
    pressed = true;
    submenu++;
  }
}

void showID() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(6, 2); lcd.print("ID:");
  lcd.setCursor(10, 2); lcd.print(return2digits(tempID));
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showAirTemp() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Air Temp:");
  lcd.setCursor(12, 2); lcd.print(getAirTemperature());
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showAirHum() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Air Hum:");
  lcd.setCursor(11, 2); lcd.print(getAirHumidity());
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showSoilTemp() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Soil Temp:");
  lcd.setCursor(13, 2); lcd.print(getSoilTemperature());
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showSoilMoist() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Soil Moist:");
  lcd.setCursor(14, 2); lcd.print(return3digits(getSoilMoisture()));
  lcd.setCursor(18, 2); lcd.print("%");
  lcd.setCursor(0, 3); lcd.write(0);
  //lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showLightInt() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Light Int:");
  lcd.setCursor(13, 2); lcd.print(return3digits(getLightIntensity()));
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showSysTemp() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Sys Temp:");
  lcd.setCursor(12, 2); lcd.print(getSystemTemperature());
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  submenuPressedRight();
}

void showSysHum() {
  refreshLCD();
  lcd.setCursor(0, 0); lcd.print("Info Menu");
  lcd.setCursor(2, 2); lcd.print("Sys Hum:");
  lcd.setCursor(12, 2); lcd.print(getSystemHumidity());
  lcd.setCursor(0, 3); lcd.write(0);
  //lcd.setCursor(19, 3); lcd.write(1);
  submenuPressedLeft();
  //submenuPressedRight();
}