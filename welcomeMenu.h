/*
   refreshLCD() clears lcd
   printMainMenu() prints basic menu data
   menuPressedRight() checks if right button is pressed
*/
void welcomeMenu() {
  refreshLCD();
  printMainMenu();
  lcd.setCursor(5, 3); lcd.print("Welcome!");
  lcd.setCursor(19, 3); lcd.write(1);
  menuPressedRight();
  //resetPosition(); 
}
