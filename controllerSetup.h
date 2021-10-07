void disable_unusedComponents() {
  //power_adc_disable();
  //power_spi_disable();
  power_usart0_disable();
  power_usart2_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_timer3_disable();
  power_timer4_disable();
  power_timer5_disable();
  //power_twi_disable();
}

void turnOFF_analogPins() {
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A14, OUTPUT);
  pinMode(A15, OUTPUT);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
  digitalWrite(A9, LOW);
  digitalWrite(A10, LOW);
  digitalWrite(A11, LOW);
  digitalWrite(A12, LOW);
  digitalWrite(A13, LOW);
  digitalWrite(A14, LOW);
  digitalWrite(A15, LOW);
}

void turnOFF_digitalPins() {
  for (int i = 28; i <= 42; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void slowArduinoDown() {
  CLKPR = 0x80;
  CLKPR = 0x01; // divided by 4
}


void turnOffLED() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

/*
   declare the buttons
   SELECT,DOWN,UP,LEFT,RIGHT
*/
void buttonMode() {
  pinMode(sel, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(GND_buttons, OUTPUT);
  digitalWrite(GND_buttons, LOW);
}


/*
   declare a stopped motor
*/
void rotorDriver() {
  digitalWrite(motorInput_1, LOW);
  digitalWrite(motorInput_2, LOW);
}


/*
   declare magnets
   declare switch toddle
*/
void rotorPosition() {
  pinMode(switchToddle, INPUT_PULLUP);
  pinMode(magnet1, INPUT_PULLUP);
  pinMode(magnet2, INPUT_PULLUP);
  pinMode(magnet4, INPUT_PULLUP);
  pinMode(magnet8, INPUT_PULLUP);
  pinMode(GND_rotor, OUTPUT);
  digitalWrite(GND_rotor, LOW);
}


/*
   declare sd card
*/
void sdCard() {
  pinMode(SS, OUTPUT);
  pinMode(Vcc_SDcard, OUTPUT);
  digitalWrite(Vcc_SDcard, HIGH);
  pinMode(GND_SDcard, OUTPUT);
  digitalWrite(GND_SDcard, LOW);
  if (!SD.begin(pinCS)) {
    return;
  }
}


/*
   setup lcd panel
   create new characters:
   left arrow, right arrow, up&down arrow, underscore
*/
void LCD() {
  lcd.begin();
  lcd.backlight();
  byte arrowLeft[] = {0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00};
  byte arrowRight[] = {0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, 0x00};
  byte arrowUpDown[] = {0x04, 0x0E, 0x1F, 0x00, 0x00, 0x1F, 0x0E, 0x04};
  byte arrowUp[] = {0x04, 0x0E, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte underscore[] = {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  lcd.createChar(0, arrowLeft);
  lcd.createChar(1, arrowRight);
  lcd.createChar(2, arrowUpDown);
  lcd.createChar(3, arrowUp);
  lcd.createChar(4, underscore);
}

/*
   gets a number
   returns a 2 char string
*/
String return2digits(int number) {
  String s;
  if (number >= 0 && number < 10) {
    s = "0"; s.concat(number);
    return s;
  }
  else {
    s = number;
    return s;
  }
}

String return3digits(int number) {
  String s;
  if (number >= 0 && number < 10) {
    s = number; s.concat("  ");
    return s;
  }
  if (number >= 10 && number < 99) {
    s = number; s.concat("  ");
    return s;
  }
  else {
    s = number;
    return s;
  }
}

/*
   clears lcd
   set cursor at location (0,0) of lcd array
*/
void clearLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

/*
   prints Menu
   prints hh:mm
   prints DD/MM/YYYY
*/
void printMainMenu() {
  lcd.print("Menu");
  lcd.setCursor(15, 0); lcd.print(return2digits(tm.Hour));
  lcd.setCursor(17, 0); lcd.print(":");
  lcd.setCursor(18, 0); lcd.print(return2digits(tm.Minute));
  lcd.setCursor(10, 1); lcd.print(return2digits(tm.Day));
  lcd.setCursor(12, 1); lcd.print("/");
  lcd.setCursor(13, 1); lcd.print(return2digits(tm.Month));
  lcd.setCursor(15, 1); lcd.print("/");
  lcd.setCursor(16, 1); lcd.print(tmYearToCalendar(tm.Year));
}


/*
   check if right button is pressed while at menu
*/
void menuPressedRight() {
  if (digitalRead(right) == LOW && backlitStatus == true) {
    menu++;
    pressed = true;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
}


/*
   check if left button is pressed while at menu
*/
void menuPressedLeft() {
  if (digitalRead(left) == LOW && backlitStatus == true) {
    menu--;
    pressed = true;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
}


/*
   check if right button is pressed while at submenu
*/
void submenuPressedRight() {
  if (digitalRead(right) == LOW && backlitStatus == true) {
    submenu++;
    pressed = true;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
}


/*
   check if left button is pressed while at submenu
*/
void submenuPressedLeft() {
  if (digitalRead(left) == LOW && backlitStatus == true) {
    submenu--;
    pressed = true;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
}

void printLeftArrow() {
  lcd.setCursor(0, 3); lcd.write(0);
}

void printRightArrow() {
  lcd.setCursor(19, 3); lcd.write(1);
}

/*
   prints underscore
   gets 3 parameters
   int1 & int2 are columns, int3 row
*/
void printUnderscoreTime(int int1, int int2, int int3) {
  lcd.setCursor(int1, int3); lcd.write(4);
  lcd.setCursor(int2, int3); lcd.write(4);
}

/*
   prints up&down arrow
   gets 2 paramets int1 culomn, int2 row of lcd arraw
*/
void printUpDownArrow(int int1, int int2) {
  lcd.setCursor(int1, int2); lcd.write(2);
}

/*
   check if time is saved
   saves actual time into the Time array
*/
void temporaryTime() {
  if (timeSaved == false) {
    RTC.read(tm);
    Time[0] = tm.Hour;
    Time[1] = tm.Minute;
    Time[2] = tm.Day;
    Time[3] = tm.Month;
    Time[4] = tmYearToCalendar(tm.Year);
    timeSaved = true;
    if (Time[1] >= 0 && Time[1] < 15)Time[1] = 15;
    else if (Time[1] >= 15 && Time[1] < 30)Time[1] = 30;
    else if (Time[1] >= 30 && Time[1] < 45)Time[1] = 45;
    else if (Time[1] >= 45) {
      Time[0] += 1;
      Time[1] = 0;
    }
  }

}



/*
   checks if a button is pressed
   clears LCD
*/
void refreshLCD() {
  if (pressed == true) {
    clearLCD();
    pressed = false;
  }
}



/*
   reset bottle position
   default position 13 (Pause location)
*/
void resetPosition() {
  RTC.read(tm);
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.print("# Resetting Position 13\t");
    myFile.print(return2digits(tm.Hour));
    myFile.print(":");
    myFile.print(return2digits(tm.Minute));
    myFile.print(" ");
    myFile.print(return2digits(tm.Day));
    myFile.print("/");
    myFile.print(return2digits(tm.Month));
    myFile.print("/");
    myFile.println(return2digits(tmYearToCalendar(tm.Year)));
    myFile.close(); // close the file
  }
  while (tempLocation != 13) {
    digitalWrite(motorInput_1, LOW);
    digitalWrite(motorInput_2, HIGH);
    tempLocation = 0;
    if (digitalRead(switchToddle) == LOW) {
      if (digitalRead(magnet1) == LOW)tempLocation += 1;
      if (digitalRead(magnet2) == LOW)tempLocation += 2;
      if (digitalRead(magnet4) == LOW)tempLocation += 4;
      if (digitalRead(magnet8) == LOW)tempLocation += 8;
      if (tempLocation == 13) {
        digitalWrite(motorInput_1, LOW);
        digitalWrite(motorInput_2, LOW);
      }
    }
  }
}


/*
  Turns off the lcd backlit
  Duration is measured in milliseconds, 60000 milliseconds = 1 minute
  Backlit turned on when SELECT button is pressed
  Time resets when a button is pressed
*/
void lcdBacklit() {
  int duration = 10000 / 2;
  if (millis() - backlitTime >= duration && backlitStatus == true) {
    lcd.noBacklight();
    lcd.noDisplay();
    backlitStatus = false;
  }
  if (( digitalRead(sel) == LOW) && backlitStatus == false) {
    delay((200 / 2));
    lcd.backlight();
    lcd.display();
    backlitStatus = true;
    backlitTime = millis();
  }
  if ((digitalRead(left) == LOW || digitalRead(right) == LOW || digitalRead(up) == LOW || digitalRead(down) == LOW || digitalRead(sel) == LOW) && backlitStatus == true) {
    backlitTime = millis();
  }

}


/*
   Prints the starting time of the program
   format: hh:mm DD/MM/YYYY
*/
void submenushowTime() {

  lcd.setCursor(2, 2); lcd.print(return2digits(Time[0]));
  lcd.setCursor(4, 2); lcd.print(":");
  lcd.setCursor(5, 2); lcd.print(return2digits(Time[1]));
  lcd.setCursor(7, 2); lcd.print(" ");
  lcd.setCursor(8, 2); lcd.print(return2digits(Time[2]));
  lcd.setCursor(10, 2); lcd.print("/");
  lcd.setCursor(11, 2); lcd.print(return2digits(Time[3]));
  lcd.setCursor(13, 2); lcd.print("/");
  lcd.setCursor(14, 2); lcd.print(Time[4]);
}


/*
   Checks if the system just restarted
*/
void rebootedSystem() {
  RTC.read(tm);
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("\n\n\n");
    myFile.println("# System rebooted");
    myFile.println("# Local Time: " + return2digits(tm.Hour) + ":" + return2digits(tm.Minute) + " " + return2digits(tm.Day) + "/" + return2digits(tm.Month) + "/" + return2digits(tmYearToCalendar(tm.Year)) + "\n");
    if (activatedGNSS) {
      myFile.println("# UTC Time: " + getUTC());
      myFile.println("# Longitude: " + getLongitudePosition());
      myFile.println("# Latitude: " + getLatitudePosition());
    }
    else {
      myFile.println("# UTC Time: -" );
      myFile.println("# Longitude: -");
      myFile.println("# Latitude: -");
    }
    myFile.print("\n# Machine ID: "); myFile.println(systemID);
    myFile.println("\n********************************\n");
    myFile.close(); // close the file
  }
}

/*
   Checks if the buttons are pressed
   gets 2 parameters, int i array and int j array position
   increments/dicrements the value stored in j location the array i
*/

void pressedUpDown(int i[], int j) {
  if (digitalRead(up) == LOW && backlitStatus == true) {
    i[j]++;
    delay(200);
  }
  if (digitalRead(down) == LOW && backlitStatus == true) {
    i[j]--;
    delay(200);
  }
}

void setSystemID(int i) {
  systemID = i;
}
