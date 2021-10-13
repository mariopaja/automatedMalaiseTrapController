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
  //resetPosition();				/*	<-	THIS SHOULD BE UNCOMMENTED, IT WILL ALLOW THE BOTTLE CHANGER TO SET BOTTLE 13 AS DEFAULT AFTER FINISHING A MANUAL PROGRAM	*/
}
