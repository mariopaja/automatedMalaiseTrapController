/*
   Sets the starting hour of the program
   temporaryTime() gets the actual time
   refreshLCD() clears LCD
   submenushowTime() prints the time
   printUpDownArrow(19, 2) prints up&down indicator arrows at location 19,2 of the LCD
   printLeftArrow() prints left arrow indicator
   printUnderscoreTime(2, 3, 3) prints underscore indicators column 2&3 row 3 for the LCD array
   printRightArrow() prints right arrow indicator
   pressedUpDown(Time, submenu - 1) changes the time stored in submenu-1 location of Time array
   hhCheck(Time, 0) checks validity of hh stored at position 0 of array Time
*/
void setStartHour() {
  temporaryTime();
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Start Time");
  submenushowTime();
  printUpDownArrow(19, 2);
  printLeftArrow();
  printUnderscoreTime(2, 3, 3);
  printRightArrow();
  submenuPressedLeft();
  submenuPressedRight();
  if (menu == 1)  pressedUpDown(Time, submenu - 1);
  if (menu == 2)  pressedUpDown(Time, submenu - 2);
  hhCheck(Time, 0);
  MMcheck(Time, 3);
}
/*
   Sets the starting minute of the program
   refreshLCD() clears LCD
   submenushowTime() prints the time
   printUpDownArrow(19, 2) prints up&down indicator arrows at location 19,2 of the LCD
   printLeftArrow() prints left arrow indicator
   printUnderscoreTime(5, 6, 3) prints underscore indicators column 5&6 row 3 for the LCD array
   printRightArrow() prints right arrow indicator
   pressedUpDown(Time, submenu - 1) changes the time stored in submenu-1 location of Time array
   mmCheck(Time, 1) checks validity of mm stored at position 1 of array Time
*/
void setStartMinute() {
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Start Time");
  submenushowTime();
  printUpDownArrow(19, 2);
  printLeftArrow();
  printUnderscoreTime(5, 6, 3);
  printRightArrow();
  delay(200);
  submenuPressedLeft();
  submenuPressedRight();
  if (menu == 1)  pressedUpDown(Time, submenu - 1);
  if (menu == 2)  pressedUpDown(Time, submenu - 2);
  mmCheck(Time, 1);
  MMcheck(Time, 3);

}
/*
   Sets the starting day of the program
   refreshLCD() clears LCD
   submenushowTime() prints the time
   printUpDownArrow(19, 2) prints up&down indicator arrows at location 19,2 of the LCD
   printLeftArrow() prints left arrow indicator
   printUnderscoreTime(8, 9, 3) prints underscore indicators column 8&9 row 3 for the LCD array
   printRightArrow() prints right arrow indicator
   pressedUpDown(Time, submenu - 1) changes the time stored in submenu-1 location of Time array
   DDcheck() checks validity of day stored at position 2 of array Time, it checks date/month/leapyear
*/
void setStartDay() {
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Start Time");
  submenushowTime();
  printUpDownArrow(19, 2);
  printLeftArrow();
  printUnderscoreTime(8, 9, 3);
  printRightArrow();
  submenuPressedLeft();
  submenuPressedRight();
  if (menu == 1)  pressedUpDown(Time, submenu - 1);
  if (menu == 2)  pressedUpDown(Time, submenu - 2);
  DDcheck();
}
/*
   Sets the starting month of the program
   refreshLCD() clears LCD
   submenushowTime() prints the time
   printUpDownArrow(19, 2) prints up&down indicator arrows at location 19,2 of the LCD
   printLeftArrow() prints left arrow indicator
   printUnderscoreTime(11, 12, 3) prints underscore indicators column 11&12 row 3 for the LCD array
   printRightArrow() prints right arrow indicator
   pressedUpDown(Time, submenu - 1) changes the time stored in submenu-1 location of Time array
   DDcheck() checks validity of day stored at position 2 of array Time, it checks date/month/leapyear
   MMcheck(Time, 3) checks validity of the month
*/
void setStartMonth() {
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Start Time");
  submenushowTime();
  printUpDownArrow(19, 2);
  printLeftArrow();
  printUnderscoreTime(11, 12, 3);
  printRightArrow();
  submenuPressedLeft();
  submenuPressedRight();
  if (menu == 1)  pressedUpDown(Time, submenu - 1);
  if (menu == 2)  pressedUpDown(Time, submenu - 2);
  MMcheck(Time, 3);
  DDcheck();
}
/*
   Sets the starting year of the program
   refreshLCD() clears LCD
   submenushowTime() prints the time
   printUpDownArrow(19, 2) prints up&down indicator arrows at location 19,2 of the LCD
   printLeftArrow() prints left arrow indicator
   printUnderscoreTime(14, 15, 3) prints underscore indicators column 14&15 row 3 for the LCD array
   printUnderscoreTime(16, 17, 3) prints underscore indicators column 16&17 row 3 for the LCD array
   printRightArrow() prints right arrow indicator
   pressedUpDown(Time, submenu - 1) changes the time stored in submenu-1 location of Time array
   YYYYcheck() checks the validity of the year
   makes correctTime false so it can be checked dureing the next step
*/
void setStartYear() {
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Start Time");
  submenushowTime();
  printUpDownArrow(19, 2);
  printLeftArrow();
  printUnderscoreTime(14, 15, 3);
  printUnderscoreTime(16, 17, 3);
  printRightArrow();
  submenuPressedLeft();
  submenuPressedRight();
  if (menu == 1)  pressedUpDown(Time, submenu - 1);
  if (menu == 2)  pressedUpDown(Time, submenu - 2);
  YYYYcheck();
  correctTime = false;
}
