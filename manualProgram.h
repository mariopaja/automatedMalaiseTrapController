
/*
   setIntervals() sets number of intervals
   refreshLCD() clears LCD
   printUpDownArrow(18, 1) prints up&down indicator arrows at location 18,1 of the LCD
   printUnderscoreTime(15, 16, 2) prints underscore indicators column 15&16 row 2 for the LCD array
   printLeftArrow() prints left arrow indicator
   printRightArrow() prints right arrow indicator
   buttons up/down increment/decrement the number of intervals
*/

void setIntervals() {
  refreshLCD();
  lcd.print("Start Program");
  lcd.setCursor(0, 1); lcd.print("Set Intervals:");
  lcd.setCursor(15, 1); lcd.print(return2digits(nrIntervals));
  if (nrIntervals < 100) lcd.setCursor(17, 1); lcd.print(" ");
  printUpDownArrow(19, 1);
  printUnderscoreTime(15, 16, 2);
  if (nrIntervals >= 100) {
    lcd.setCursor(17, 2); lcd.write(4);
  } else lcd.setCursor(17, 2); lcd.print(" ");
  printLeftArrow();
  printRightArrow();
  if (digitalRead(up) == LOW && backlitStatus == true) {
    nrIntervals++;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
  if (digitalRead(down) == LOW && backlitStatus == true) {
    nrIntervals--;
    lcd.backlight();
    backlitTime = millis();
    delay(200);
  }
}

/*
   checks if the time set is correct (now or in the future)
   setIntervals() sets number of intervals
   nrIntervalCheck() checks number of intervals
*/
void intervals() {
  if (correctTime == false) correctTime = checkDateTime();
  else {
    setIntervals();
    submenuPressedLeft();
    submenuPressedRight();
    nrIntervalCheck();
  }
}

/*
   refreshLCD() clears LCD
   printMainMenu() prints basic menu information
   press select to set up the new program
*/
void manualProgram() {
  refreshLCD();
  printMainMenu();
  lcd.setCursor(0, 3); lcd.write(0);
  lcd.setCursor(3, 3); lcd.print("Manual Program");
  lcd.setCursor(19, 3); lcd.write(1);
  menuPressedLeft();
  menuPressedRight();
  if (digitalRead(sel) == LOW && backlitStatus == true) {
    submenu++;
    pressed = true;
  }
  timeSaved = false;
}

/*
   refreshLCD() clears LCD
   submenuPressedLeft() checks if left button is pressed
   for loop to setup interval data for i number of intervals
   for loop to setup interval data for each interval
   minimum bottle is 1
   duration is saved in minutes
   tempDuration saves the total amount of minutes
   days converts total time into days
   hours turns the remaining minutes into hours
   mins the remaining duration
   when j=0 increases/decreases day duration (+/- 1440 minutes)
   when j=1 increases/decreases hour duration (+/- 60 minutes)
   when j=2 increases/decreases minute duration (+/- 1 minute)
   when j=3 sets number of bottles per interval
*/
void configureIntervals() {

  refreshLCD();
  submenuPressedLeft();

  /*========Start Interval Configuration========*/
  for (int i = 0; i < nrIntervals;) {

    /*==========Configure 4 data of each Interval==========*/
    for (int j = 0; j < 4;) {
      int tempDuration = intervalData[(i * 2) + 1];
      int days = tempDuration / (24 * 60); tempDuration = tempDuration % (24 * 60);
      int hours = tempDuration / 60; tempDuration = tempDuration % 60;
      int mins = tempDuration;
      refreshLCD();
      lcd.print("Interval");
      lcdBacklit();

      /*=============Interval Duration dd=============*/
      if (j == 0) {
        if (digitalRead(up) == LOW && backlitStatus == true) {
          intervalData[(i * 2) + 1] += (24 * 60);
          delay(200);
        }
        if (digitalRead(down) == LOW && days > 0 && backlitStatus == true) {
          intervalData[(i * 2) + 1] -= (24 * 60);
          delay(200);
        }
        printUnderscoreTime(4, 5, 3);
      }

      /*=============Interval Duration hh=============*/

      if (j == 1) {
        if (digitalRead(up) == LOW && backlitStatus == true) {
          intervalData[(i * 2) + 1] += 60;
          delay(200);
        }
        if (digitalRead(down) == LOW && (days != 0 || hours > 0) && backlitStatus == true) {
          intervalData[(i * 2) + 1] -= 60;
          delay(200);
        }
        printUnderscoreTime(7, 8, 3);
        //lcd.setCursor(15, 3); lcd.print("   ");
      }

      /*=============Interval Duration mm=============*/
      if (j == 2) {
        if (digitalRead(up) == LOW && backlitStatus == true) {
          intervalData[(i * 2) + 1] += 15;
          delay(200);
        }
        if (digitalRead(down) == LOW && (days != 0 || hours != 0 || mins > 15) && backlitStatus == true) {
          intervalData[(i * 2) + 1] -= 15;
          delay(200);
        }
        printUnderscoreTime(10, 11, 3);
        //lcd.setCursor(16, 3);
      }

      /*=============Interval Duration bottle=============*/
      if (j == 3) {
        if (digitalRead(up) == LOW && backlitStatus == true) {
          intervalData[(i * 2)]++;
          if (intervalData[(i * 2)] > 13) intervalData[(i * 2)] = 1;
          delay(200);
        }
        if (digitalRead(down) == LOW && backlitStatus == true) {
          intervalData[(i * 2)]--;
          if (intervalData[(i * 2)] < 1) intervalData[(i * 2)] = 13;
          delay(200);
        }
        printUnderscoreTime(16, 17, 3);

      }

      lcd.setCursor(9, 0); lcd.print(return2digits(i + 1));
      lcd.setCursor(2, 2); lcd.print("D:");
      lcd.setCursor(4, 2); lcd.print(return2digits(days));
      lcd.setCursor(6, 2); lcd.print("d");
      lcd.setCursor(7, 2); lcd.print(return2digits(hours));
      lcd.setCursor(9, 2); lcd.print("h");
      lcd.setCursor(10, 2); lcd.print(return2digits(mins));
      lcd.setCursor(12, 2); lcd.print("m");
      lcd.setCursor(14, 2); lcd.print("B:");
      lcd.setCursor(16, 2);

      if (intervalData[(i * 2)] != 13) lcd.print(return2digits(intervalData[(i * 2)]));
      else lcd.print("P.");

      printUpDownArrow(19, 2);
      printLeftArrow();
      printRightArrow();


      if (digitalRead(right) == LOW && backlitStatus == true) {
        j++;
        pressed = true;
        if (j == 4) i++;
        delay(200);
      }

      if (digitalRead(left) == LOW && backlitStatus == true) {
        j--;
        pressed = true;
        if (j < 0) {
          j = 3;
          i--;
          if (i < 0) {
            submenu--;
            delay(200);
            return;
          }
        }
        delay(200);
      }
    }
  }
  submenu++;
}



/*
   startIntervals() : Start Manual Program
                    : Iterrate all saved intervals
                    : Save data in SD card
                    : Update LCD display

*/
void startIntervals() {
  /*=====================Update LCD=======================*/
  /*===========Save program Start on SD Card==============*/
  if (pressed == true) {
    clearLCD();
    RTC.read(tm);
    lcd.print("Waiting...");

    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("# Starting New Program");
      myFile.println("# Local Time: " + return2digits(tm.Hour) + ":" + return2digits(tm.Minute) + " " + return2digits(tm.Day) + "/" + return2digits(tm.Month) + "/" + return2digits(tmYearToCalendar(tm.Year)));
      myFile.print("# UTC Time: ");
      if (activatedGNSS) {
          myFile.println(getUTC());
      }
      else {
          myFile.println("-");
      }
      myFile.println("# Waiting Start Time...");
      myFile.println("\n********************************\n");
      myFile.close(); // close the file
    }
    pressed = false;
  }

  /*===================== Wait Start Time =======================*/
  if (Time[4] == tmYearToCalendar(tm.Year) && Time[3] == tm.Month && Time[2] == tm.Day && Time[0] == tm.Hour && Time[1] <= tm.Minute) {

    //SMS("Manual Program Started");
    //if(activatedSIM7000E)SMS(createMessage(systemID,"Manual Program Started"));
    setProgramID();
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("- Manual Program");
      myFile.println("\n********************************\n");
      myFile.close(); // close the file
    }

    unsigned long time;
    /*============= Starting Intervals ===============*/
    for (int i = 0; i < nrIntervals; i++) {
      clearLCD();
      lcd.print("Interval:");
      lcd.setCursor(10, 0);
      lcd.print(i + 1);
      lcdBacklit();

      bool positionSet = false;
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile) {
        myFile.print("- Interval: "); myFile.print(i + 1);
        myFile.close(); // close the file
      }

      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile) {
        myFile.println("\n\n- Bottle\t\t\t\t|\tAT(°C)\t\t|\tRAH (%)\t\t|\tST (°C)\t\t|\tSRM (%)\t\t|\tL (lx)\t\t|\tLocal Time\t\t|\tUTC Time");
        myFile.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        myFile.close(); // close the file
      }
      /*========= Set Bottle Position==========*/

      //          while (positionSet == false) {
      //         digitalWrite(motorInput_1, LOW);
      //         digitalWrite(motorInput_2, HIGH);
      //         int tempLocation = 0;
      //
      //         if (digitalRead(switchToddle) == LOW) {
      //           if (digitalRead(magnet1) == LOW)tempLocation += 1;
      //           if (digitalRead(magnet2) == LOW)tempLocation += 2;
      //           if (digitalRead(magnet4) == LOW)tempLocation += 4;
      //           if (digitalRead(magnet8) == LOW)tempLocation += 8;
      //           if (tempLocation == intervalData[(2 * i)]) {
      //             digitalWrite(motorInput_1, LOW);
      //             digitalWrite(motorInput_2, LOW);
      //             positionSet = true;
      //           }
      //         }
      //
      //        }

      /*=== Save Interval Data on SD Card ===*/
      RTC.read(tm);


      /*======== Start Interval ===========*/
      time = millis();
      unsigned long tempTime = intervalData[(2 * i) + 1] * 60000;

      /*======== Update LCD ===========*/
      /*= Save Sensor Data in SD Card =*/
      while (millis() - time < tempTime) {
        lcdBacklit();
        lcd.setCursor(0, 1); lcd.print("Bottle:");
        lcd.setCursor(8, 1); lcd.print(intervalData[(2 * i)]);
        RTC.read(tm);
        saveSensorData(intervalData[(2 * i)]);
        /*= Wait 5 Minutes before the next sensor reading =*/
        unsigned long waitTime = millis();
        while (millis() - waitTime < 300000) {/*300000*/
          lcdBacklit();

          //checkBatteryLevel();
          //checkSystemFallenDown();

          if (digitalRead(left) == LOW && backlitStatus == true) {
            menu = 0;
            submenu = 0;
            tempLocation = 0;
            pressed = true;

            break;
          }
        }
      }
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile) {
        myFile.println("\n\n");
        myFile.close(); // close the file
      }
    }

    /*=============== End of Program ===============*/
    /*============ Save data in SD Card ============*/

    RTC.read(tm);
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("# Program Ended");
      myFile.print("# Local Time: ");
      myFile.print(return2digits(tm.Hour)); myFile.print(":");
      myFile.print(return2digits(tm.Minute)); myFile.print(" ");
      myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.println(return2digits(tmYearToCalendar(tm.Year)));
      myFile.print("\n");
      myFile.print("# UTC Time: ");
      if (activatedGNSS) {
          myFile.println(getUTC());
      }
      else {
          myFile.println("-");
      }
      myFile.println("********************************\n");
      myFile.close(); // close the file
    }


    /*============ Redirect to Welcome Menu ============*/
    menu = 0;
    submenu = 0;
    tempLocation = 0;
    pressed = true;
    //if(activatedSIM7000E)SMS(createMessage(systemID,"Manual Program Ended"));
  }
  else {
    lcdBacklit();
    //waits for the start time
    //UNCOMMENT
    //       while (tempLocation != 13) {
    //          lcdBacklit();
    //         digitalWrite(motorInput_1, LOW);
    //         digitalWrite(motorInput_2, HIGH);
    //         tempLocation = 0;
    //         if (digitalRead(switchToddle) == LOW) {
    //           if (digitalRead(magnet1) == LOW)tempLocation += 1;
    //           if (digitalRead(magnet2) == LOW)tempLocation += 2;
    //           if (digitalRead(magnet4) == LOW)tempLocation += 4;
    //           if (digitalRead(magnet8) == LOW)tempLocation += 8;
    //           if (tempLocation == 13) {
    //             digitalWrite(motorInput_1, LOW);
    //             digitalWrite(motorInput_2, LOW);
    //           }
    //         }
    //       }
  }

}
