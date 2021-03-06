/*
	configMenu()    :   prints the config menu
					:   clears the lcd
					:   prints data on lcd
*/
void configMenu() {
	refreshLCD();
	printMainMenu();
	lcd.setCursor(0, 3); lcd.write(0);
	lcd.setCursor(3, 3); lcd.print("Config Data");
	lcd.setCursor(19, 3); lcd.write(1);
	menuPressedLeft();
	menuPressedRight();
	if (digitalRead(sel) == LOW && backlitStatus == true) {
		pressed = true;
		submenu++;
	}
	timeSaved = false;
}

/*
   gets the actual machine id
   prints the actual machine id
   you can change the id by pressing up/down buttons
   the id is saved on EEPROM (long term memory and it will not be erased in case of power off
*/
/*
void setID() {
	refreshLCD();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(3, 2); lcd.print("Set ID:");
	lcd.setCursor(10, 2); lcd.print(return2digits(tempID));

	lcd.setCursor(0, 3); lcd.write(0);
	printUnderscoreTime(10, 11, 3);
	lcd.setCursor(19, 3); lcd.write(1);
	submenuPressedLeft();
	submenuPressedRight();
	if (submenu != 1 && tempID != machineID) {
		EEPROM.put(0, tempID);
		machineID = tempID;
	}
	if (digitalRead(up) == LOW && backlitStatus == true) {
		tempID++;
		delay(200);
	}
	if (digitalRead(down) == LOW && backlitStatus == true) {
		tempID--;
		delay(200);
	}
	tempIDcheck();

}
*/
/*
   SetHour()    :   gets the saved hh on RTC and saves it on Time[] array
				:   by pressing up/down it will change hh
				:   time will be saved after you have exited from the submenu towards the main menu
*/
void SetHour() {
	refreshLCD();
	RTC.read(tm);
	temporaryTime();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(0, 1); lcd.print("Set Time:");
	submenushowTime();
	printUpDownArrow(19, 2);
	printLeftArrow();
	printUnderscoreTime(2, 3, 3);
	printRightArrow();
	submenuPressedLeft();
	submenuPressedRight();
	pressedUpDown(Time, submenu - 1);
	if (submenu < 1) {
		tm.Hour = Time[0];
		tm.Minute = Time[1];
		tm.Second = 0;
		tm.Day = Time[2];
		tm.Month = Time[3];
		tm.Year = CalendarYrToTm(Time[4]);
		RTC.write(tm);
	}
	hhCheck(Time, 0);
}


/*
	SetMinute()	:	gets the saved mm on RTC and saves it temporary on Time[] array
				:	by pressing up/down it will change mm
				:	time will be saved after you have exited from the submenu towards the menu
				:	Be careful to have set the exact time when you exit the menu   
*/
void SetMinute() {
	refreshLCD();
	temporaryTime();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(0, 1); lcd.print("Set Time:");
	submenushowTime();
	printUpDownArrow(19, 2);
	printLeftArrow();
	printUnderscoreTime(5, 6, 3);
	printRightArrow();
	submenuPressedLeft();
	submenuPressedRight();
	pressedUpDown(Time, submenu - 1);
	mmCheck(Time, 1);
}


/*
	SetDate()	:	gets the saved DD on RTC and saves it temporary on Time[] array
				:	by pressing up/down it will change DD
				:	time will be saved after you have exited from the submenu towards the menu
				:	Be careful to have set the exact time when you exit the menu
*/
void SetDate() {
	refreshLCD();
	temporaryTime();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(0, 1); lcd.print("Set Time:");
	submenushowTime();
	printUpDownArrow(19, 2);
	printLeftArrow();
	printUnderscoreTime(8, 9, 3);
	printRightArrow();
	submenuPressedLeft();
	submenuPressedRight();
	pressedUpDown(Time, submenu - 1);
	DDcheck();
}


/*
	SetMonth()	:	gets the saved MM on RTC and saves it temporary on Time[] array
				:	by pressing up/down it will change MM
				:	time will be saved after you have exited from the submenu towards the menu
				:	Be careful to have set the exact time when you exit the menu
*/
void SetMonth() {
	refreshLCD();
	temporaryTime();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(0, 1); lcd.print("Set Time:");
	submenushowTime();
	printUpDownArrow(19, 2);
	printLeftArrow();
	printUnderscoreTime(11, 12, 3);
	printRightArrow();
	submenuPressedLeft();
	submenuPressedRight();
	pressedUpDown(Time, submenu - 1);
	MMcheck(Time, 3);
	DDcheck();
}


/*
	SetYear()	:	gets the saved YYYY on RTC and saves it temporary on Time[] array
				:	by pressing up/down it will change YYYY
				:	time will be saved after you have exited from the submenu towards the menu
				:	Be careful to have set the exact time when you exit the menu
*/
void SetYear() {
	refreshLCD();
	temporaryTime();
	lcd.setCursor(0, 0); lcd.print("Confing Menu");
	lcd.setCursor(0, 1); lcd.print("Set Time:");
	submenushowTime();
	printUpDownArrow(19, 2);
	printLeftArrow();
	printUnderscoreTime(14, 15, 3);
	printUnderscoreTime(16, 17, 3);
	//printRightArrow();
	submenuPressedLeft();
	// submenuPressedRight();
	pressedUpDown(Time, submenu - 1);
	//YYYYcheck();
}
