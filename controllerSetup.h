void disable_unusedComponents() {
  power_usart0_disable();
  power_usart2_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_timer3_disable();
  power_timer4_disable();
  power_timer5_disable();
}


/*
    turnOFF_analogPins()    :   declare analog pins as output
                            :   declare analog pins as GND
*/
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

/*
    turnOFF_digitalPins()   :   declare digital pins as output
                            :   declare digital pins as output
*/
void turnOFF_digitalPins() {
  for (int i = 28; i <= 42; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

/*
    slowArduinoDown()   :   changes the prescaler of the microprocessor
                        :   0x80 -> activates the prescaler
                        :   0x01 -> frequency divided by 4 (2^2)
                        :   NOT IMPLEMENTED
*/
void slowArduinoDown() {
  CLKPR = 0x80;
  CLKPR = 0x01;
}

/*
    turnOffLED()    :   declare pin 13 as output
                    :   declare pin 13 as GND
*/
void turnOffLED() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

/*
    buttonMode()    :   declare the buttons of the keypad
                    :   SELECT,DOWN,UP,LEFT,RIGHT
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
    rotorDriver()   :   declare a stopped motor
                    :   motorInput_1 -> LOW & motorInput_2 -> LOW
                    :   This might change depending on the H-Bridge that is used
*/
void rotorDriver() {
  digitalWrite(motorInput_1, LOW);
  digitalWrite(motorInput_2, LOW);
}


/*
    rotorPosition() :   declare magnets
                    :   declare switch toddle
                    :   declare GND pin of the plug
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
    clearLCD()  :   clears lcd
                :   set cursor at location (0,0) of lcd array
*/
void clearLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
}


/*
    sdCard()    :   declare SD card
                :   initiliaze SD card
                :   check if sD card is recognised by the system
*/
void sdCard() {
 pinMode(Vcc_SDcard, OUTPUT);
  pinMode(GND_SDcard, OUTPUT);
  digitalWrite(Vcc_SDcard, HIGH);

  digitalWrite(GND_SDcard, LOW);
  pinMode(pinCS, OUTPUT);

  
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("SD card");
  delay(200);

  if (SD.begin()) {
    lcd.setCursor(0, 2); lcd.print("OK");
    delay(4000);
  }
  else {
    clearLCD();
    lcd.setCursor(0, 2); lcd.print("Failed!");
    lcd.setCursor(0, 3); lcd.print("SKIP SD?        YES");
    lcd.setCursor(19, 3); lcd.write(1);
    while (1) {
      if (digitalRead(right) == LOW){pressed == true;break;}
    }

  }
}


/*
    LCD()   :   setup lcd panel
            :   initiliaze lcd panel
            :   create new characters -> left arrow, right arrow, up&down arrow, underscore
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
    return2digits() :   turns a single digit number into a two character String
                    :   input -> integer
                    :   output -> String
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

/*
    return3digits() :   turns a single digit number into a tree character String
                    :   input -> integer
                    :   output -> String
*/
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
    printMainMenu() :   prints Menu
                    :   prints hh:mm
                    :   prints DD/MM/YYYY
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
    menuPressedRight()  :   check if right button is pressed
                        :   increments the menu level
                        :   resets the lcd backlit counting
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
    menuPressedLeft()  :   check if left button is pressed
                       :   decrements the menu level
                       :   resets the lcd backlit counting
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
    submenuPressedRight()  :   check if right button is pressed
                           :   increments the submenu level
                           :   resets the lcd backlit counting
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
    submenuPressedLeft()  :   check if left button is pressed
                          :   decrements the submenu level
                          :   resets the lcd backlit counting
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
    printUnderscoreTime()   :   used as an undersore cursor for the time
                            :   gets 3 parameters -> int1 & int2 are columns, int3 row
                            :   int1 column of first digit
                            :   int2 column of second digit
                            :   int3 row where it showld be located
                            :   underscore is located 1 low below the digit!
*/
void printUnderscoreTime(int int1, int int2, int int3) {
  lcd.setCursor(int1, int3); lcd.write(4);
  lcd.setCursor(int2, int3); lcd.write(4);
}

/*
    printUpDownArrow()  :   prints up & down arrow that indicates that the data can be changed
                        :   gets 2 paramets -> int1 culomn, int2 row of lcd arraw
*/
void printUpDownArrow(int int1, int int2) {
  lcd.setCursor(int1, int2); lcd.write(2);
}

/*
    temporaryTime() :   used as a temporaty clock
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
    refreshLCD()    :   checks if a button is pressed
                    :   clears LCD
*/
void refreshLCD() {
  if (pressed == true) {
    clearLCD();
    pressed = false;
  }
}



/*
    resetPosition() :   activates the motor rotation to set the bottle to the pause position
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
    lcdBacklit()    :   Turns off the lcd backlit
                    :   turns off the lcd panel
                    :   Duration is measured in milliseconds, 60000 milliseconds = 1 minute
                    :   Backlit turned on when SELECT button is pressed
                    :   Time resets when a button is pressed
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
   submenushowTime()    :   Prints the time that is previously saved on the temporary clock
                        :   format: hh:mm DD/MM/YYYY
                        :   used at program setup to select the start time
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
    rebootedSystem()    :   Checks if the system rebooted
                        :   Saves system information in the SD card -> boot time (RTC & UTC), location (latitude, longtitude)
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
    pressedUpDown() :   Checks if the buttons up & down are pressed
                    :   gets 2 parameters -> int i array and int j array position
                    :   increments/dicrements the value stored in j location the array i
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

/*
    setSystemID()   :   sets system ID
*/
void setSystemID(int i) {
  systemID = i;
}
