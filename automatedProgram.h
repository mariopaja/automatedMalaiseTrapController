/*
	automatedProgram()  :   Print the Automated Menu on the main Menu
						:   refreshLCD() -> resets the lcd
						:   printMainMenu() -> prints menu information
						:   declare temporary saved time as false

*/
void automatedProgram() {
	refreshLCD();
	printMainMenu();
	lcd.setCursor(0, 3); lcd.write(0);
	lcd.setCursor(4, 3); lcd.print("Auto Program");
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
	printEndProgram()   :   Print the end program data on SD card
						:   print RTC and UTC time on the SD card
*/
void printEndProgram() {
	RTC.read(tm);
	myFile = SD.open("test.txt", FILE_WRITE);
	if (myFile) {
		myFile.println("\n\n# Program Ended");
		myFile.print("# Local Time: ");
		myFile.print(return2digits(tm.Hour)); myFile.print(":");
		myFile.print(return2digits(tm.Minute)); myFile.print(" ");
		myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.println(return2digits(tmYearToCalendar(tm.Year)));
		myFile.print("\n");
		if (activatedGNSS) {
			myFile.print("# UTC Time: ");
			myFile.println(getUTC());
			myFile.print("\n");
		}
		else {
			myFile.println("# UTC Time: -\n");
		}
		myFile.println("********************************\n");
		myFile.close(); // close the file
	}

}

/*
	setBottle() :   activate the motor rotation
				:   check the bottle location
				:   stop the motor rotation
*/
void setBottle(int bottlePosition) {
	while (tempLocation != bottlePosition) {
		lcdBacklit();
		digitalWrite(motorInput_1, LOW);
		digitalWrite(motorInput_2, HIGH);
		tempLocation = 0;
		if (digitalRead(switchToddle) == LOW) {
			if (digitalRead(magnet1) == LOW)tempLocation += 1;
			if (digitalRead(magnet2) == LOW)tempLocation += 2;
			if (digitalRead(magnet4) == LOW)tempLocation += 4;
			if (digitalRead(magnet8) == LOW)tempLocation += 8;
			if (tempLocation == bottlePosition) {
				digitalWrite(motorInput_1, LOW);
				digitalWrite(motorInput_2, LOW);
			}
		}
	}
}

/*
	programSelector()    :  Choose between the 4 available automated programs
						 :  temporaryTime() -> reads the actual time and uses it as a start time for the program
						 :  refreshLCD() -> resets the lcd
						 :  programCheck() -> resets the program counting
*/

void programSelector() {
	temporaryTime();
	refreshLCD();
	lcd.print("Start Program");
	lcd.setCursor(0, 1); lcd.print(programs[program2select]);
	printUpDownArrow(19, 1);
	if (digitalRead(up) == LOW && backlitStatus == true) {
		program2select++;
		delay(200);
	}
	if (digitalRead(down) == LOW && backlitStatus == true) {
		program2select--;
		delay(200);
	}
	printLeftArrow();
	printRightArrow();
	submenuPressedLeft();
	submenuPressedRight();
	programCheck();
}

/*
   startProgram() : Wait for the Starting Time
				  : Start the selected Automated Program
					- Illuminance Program
					- Soil Moisture
					- Soil Temperature
					- Air Humidity
				  : Save Program Data on the logData
*/

void startProgram() {

	/*==== checks is the selected start time is not in the past ====*/
	if (checkDateTime()) {

		/*==== update lcd & save data in the sd card*/
		if (pressed == true) {
			clearLCD();
			RTC.read(tm);
			lcd.print("Waiting...");
			myFile = SD.open("test.txt", FILE_WRITE);
			if (myFile) {
				myFile.println("\n# Starting New Program ");
				myFile.print("# Local Time: ");
				myFile.print(return2digits(tm.Hour)); myFile.print(":");
				myFile.print(return2digits(tm.Minute)); myFile.print(" ");
				myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.println(return2digits(tmYearToCalendar(tm.Year)));
				myFile.print("# UTC Time: ");
				if (activatedGNSS) {
					myFile.println(getUTC());
				}
				else {
					myFile.println("-");
				}
				myFile.println("# Waiting Start Time...\n");
				myFile.println("********************************\n");
				myFile.close(); // close the file
			}
			pressed = false;
		}

		/*==== check if the RTC tiem matches with the start time ====*/
		if (Time[4] == tmYearToCalendar(tm.Year) && Time[3] == tm.Month && Time[2] == tm.Day && Time[0] == tm.Hour && Time[1] <= tm.Minute) {
			clearLCD();
			int bottlePosition = 13;
			unsigned long time;

			/*==== sets program2select to the program ID number ====*/
			setProgramID();

			/*==== light intensity program ====*/
			if (program2select == 0) {

				/*==== print the data header in the sd card ====*/
				RTC.read(tm);
				myFile = SD.open("test.txt", FILE_WRITE);
				if (myFile) {
					myFile.println("- Illuminance Program\n\n");
					myFile.println("- Bottle\t\t\t\t|\tAT(°C)\t\t|\tRAH (%)\t\t|\tST (°C)\t\t|\tSRM (%)\t\t|\tL (lx)\t\t|\tLocal Time\t\t|\tUTC Time");
					myFile.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					myFile.close(); // close the file
				}

				/*==== declare lightIntensity as local variable ====*/
				int lightIntensity = 0;

				/*==== start the study loop ====*/
				/*==== look terminated only by left button click ====*/
				while (digitalRead(left) != LOW) {

					/*==== read sensor data & select bottle ====*/
					lightIntensity = getLightIntensity();
					if (lightIntensity > 0 && lightIntensity <= 200) bottlePosition = 1;
					if (lightIntensity > 200 && lightIntensity <= 400) bottlePosition = 2;
					if (lightIntensity > 400 && lightIntensity <= 800) bottlePosition = 3;
					if (lightIntensity > 800 && lightIntensity <= 2200) bottlePosition = 4;
					if (lightIntensity > 2200 && lightIntensity <= 5000) bottlePosition = 5;
					if (lightIntensity > 5000 && lightIntensity <= 7000) bottlePosition = 6;
					if (lightIntensity > 7000 && lightIntensity <= 10000) bottlePosition = 7;
					if (lightIntensity > 10000 && lightIntensity <= 15000) bottlePosition = 8;
					if (lightIntensity > 15000 && lightIntensity <= 20000) bottlePosition = 9;
					if (lightIntensity > 20000 && lightIntensity <= 25000) bottlePosition = 10;
					if (lightIntensity > 25000 && lightIntensity <= 30000) bottlePosition = 11;
					if (lightIntensity > 30000 && lightIntensity <= 35000) bottlePosition = 12;
					if (lightIntensity < 0 || lightIntensity > 35000) bottlePosition = 13;

					/*==== print lcd information ====*/
					lcdBacklit();
					lcd.setCursor(0, 1);
					lcd.print("Bottle:");
					lcd.setCursor(8, 1);
					lcd.print(bottlePosition);

					//setBottle(bottlePosition);                          /*==== <- THIS NEEDS TO BE UNCOMMENTED BEFORE UPLOADED TO THE MICROCONTROLLER ====*/
					//checkBatteryLevel();                                /*==== <- BATTERY CHECK HARDWARE NOT YET IMPLEMENTED ====*/
					//checkSystemFallenDown();                            /*==== <- ACCELEROMETER NOT YET PLACED UNDER THE CONTROLLER LID ====*/

					/*==== read RTC time ====*/
					RTC.read(tm);

					/*==== save sensor data in SD card ====*/
					saveSensorData(bottlePosition);

					/*==== start pause loop for 5 minutes ====*/
					time = millis();
					unsigned long tempTime = 300000;
					while (millis() - time < tempTime) {
						lcdBacklit();
						if (digitalRead(left) == LOW && backlitStatus == true) {
							menu = 0;
							submenu = 0;
							tempLocation = 0;
							pressed = true;
							break;
						}
					}
				}

				/*==== print end program data ====*/
				printEndProgram();

				/*==== send SMS notification to the user ====*/
				if (activatedSMS)SMS(createMessage(systemID, "Illuminance Program Ended"));
			}

			/*==== soil temperature program ====*/
			if (program2select == 1) {

				/*==== declare soilTemperature as a float local variable*/
				float soilTemperature = 0.0;

				/*==== print the data header in the sd card ====*/
				myFile = SD.open("test.txt", FILE_WRITE);
				if (myFile) {
					myFile.println("- Soil Temperature Program\n\n");
					myFile.println("- Bottle\t\t\t\t|\tAT(°C)\t\t|\tRAH (%)\t\t|\tST (°C)\t\t|\tSRM (%)\t\t|\tL (lx)\t\t|\tLocal Time\t\t|\tUTC Time");
					myFile.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					myFile.close(); // close the file
				}

				/*==== start the study loop ====*/
				/*==== loop terminated only by left button click ====*/
				while (digitalRead(left) != LOW) {

					/*==== read sensor data & select bottle ====*/
					/*==== FLOAT POINTS! ====*/
					soilTemperature = roundf(getSoilTemperature() * 100) / 100.0;
					if (soilTemperature > 21.00 && soilTemperature <= 21.10) bottlePosition = 1;
					if (soilTemperature > 21.10 && soilTemperature <= 21.15) bottlePosition = 2;
					if (soilTemperature > 21.15 && soilTemperature <= 21.20) bottlePosition = 3;
					if (soilTemperature > 21.20 && soilTemperature <= 21.25) bottlePosition = 4;
					if (soilTemperature > 21.25 && soilTemperature <= 21.30) bottlePosition = 5;
					if (soilTemperature > 21.30 && soilTemperature <= 21.35) bottlePosition = 6;
					if (soilTemperature > 21.35 && soilTemperature <= 21.40) bottlePosition = 7;
					if (soilTemperature > 21.40 && soilTemperature <= 21.50) bottlePosition = 8;
					if (soilTemperature > 21.50 && soilTemperature <= 21.55) bottlePosition = 9;
					if (soilTemperature > 21.55 && soilTemperature <= 21.60) bottlePosition = 10;
					if (soilTemperature > 21.60 && soilTemperature <= 21.65) bottlePosition = 11;
					if (soilTemperature > 21.65 && soilTemperature <= 21.70) bottlePosition = 12;
					if (soilTemperature < 21.00 || soilTemperature > 21.70) bottlePosition = 13;

					/*==== print lcd information ====*/
					lcdBacklit();
					lcd.setCursor(0, 1);
					lcd.print("Bottle:");
					lcd.setCursor(8, 1);
					lcd.print(bottlePosition);

					//setBottle(bottlePosition);                          /*==== <- THIS NEEDS TO BE UNCOMMENTED BEFORE UPLOADED TO THE MICROCONTROLLER ====*/
					//checkBatteryLevel();                                /*==== <- BATTERY CHECK HARDWARE NOT YET IMPLEMENTED ====*/
					//checkSystemFallenDown();                            /*==== <- ACCELEROMETER NOT YET PLACED UNDER THE CONTROLLER LID ====*/

					/*==== read RTC time ====*/
					RTC.read(tm);

					/*==== save sensor data in SD card ====*/
					saveSensorData(bottlePosition);

					/*==== start pause loop for 5 minutes ====*/
					time = millis();
					unsigned long tempTime = 300000;
					while (millis() - time < tempTime) {
						lcdBacklit();
						if (digitalRead(left) == LOW && backlitStatus == true) {
							menu = 0;
							submenu = 0;
							tempLocation = 0;
							pressed = true;
							break;
						}
					}
				}

				/*==== print end program data ====*/
				printEndProgram();

				/*==== send SMS notification to the user ====*/
				if (activatedSMS)SMS(createMessage(systemID, "Soil Temperature Program Ended"));
			}

			/*==== soil moisture program ====*/
			if (program2select == 2) {

				/*==== declare soil moisture as local variable ====*/
				int soilMoisture = 0;

				/*==== print the data header in the sd card ====*/
				myFile = SD.open("test.txt", FILE_WRITE);
				if (myFile) {
					myFile.println("- Soil Moisture Program\n\n");

					myFile.println("- Bottle\t\t\t\t|\tAT(°C)\t\t|\tRAH (%)\t\t|\tST (°C)\t\t|\tSRM (%)\t\t|\tL (lx)\t\t|\tLocal Time\t\t|\tUTC Time");
					myFile.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					myFile.close(); // close the file
				}

				/*==== read sensor data & select bottle ====*/
				while (digitalRead(left) != LOW) {
					soilMoisture = getSoilMoisture();
					if (soilMoisture >= 0 && soilMoisture <= 5) bottlePosition = 1;
					if (soilMoisture > 5 && soilMoisture <= 10) bottlePosition = 2;
					if (soilMoisture > 10 && soilMoisture <= 15) bottlePosition = 3;
					if (soilMoisture > 15 && soilMoisture <= 20) bottlePosition = 4;
					if (soilMoisture > 20 && soilMoisture <= 30) bottlePosition = 5;
					if (soilMoisture > 30 && soilMoisture <= 40) bottlePosition = 6;
					if (soilMoisture > 40 && soilMoisture <= 50) bottlePosition = 7;
					if (soilMoisture > 50 && soilMoisture <= 60) bottlePosition = 8;
					if (soilMoisture > 60 && soilMoisture <= 70) bottlePosition = 9;
					if (soilMoisture > 70 && soilMoisture <= 80) bottlePosition = 10;
					if (soilMoisture > 80 && soilMoisture <= 90) bottlePosition = 11;
					if (soilMoisture > 90 && soilMoisture <= 100) bottlePosition = 12;
					else if (soilMoisture < 0.0 || soilMoisture > 100.0) bottlePosition = 13;

					/*==== print lcd information ====*/
					lcdBacklit();
					lcd.setCursor(0, 1);
					lcd.print("Bottle:");
					lcd.setCursor(8, 1);
					lcd.print(bottlePosition);

					//setBottle(bottlePosition);                          /*==== <- THIS NEEDS TO BE UNCOMMENTED BEFORE UPLOADED TO THE MICROCONTROLLER ====*/
					//checkBatteryLevel();                                /*==== <- BATTERY CHECK HARDWARE NOT YET IMPLEMENTED ====*/
					//checkSystemFallenDown();                            /*==== <- ACCELEROMETER NOT YET PLACED UNDER THE CONTROLLER LID ====*/

					/*==== read RTC time ====*/
					RTC.read(tm);

					/*==== save sensor data in SD card ====*/
					saveSensorData(bottlePosition);

					/*==== start pause loop for 5 minutes ====*/
					time = millis();
					unsigned long tempTime = 300000;
					while (millis() - time < tempTime) {
						lcdBacklit();
						if (digitalRead(left) == LOW && backlitStatus == true) {
							menu = 0;
							submenu = 0;
							tempLocation = 0;
							pressed = true;
							break;
						}
					}
				}

				/*==== print end program data ====*/
				printEndProgram();

				/*==== send SMS notification to the user ====*/
				if (activatedSMS)SMS(createMessage(systemID, "Soil Moisture Program Ended"));
			}

			/*==== air humidity program ====*/
			if (program2select == 3) {

				/*==== declare soil moisture as local variable ====*/
				float airHumidity = 0.0;

				/*==== print the data header in the sd card ====*/
				myFile = SD.open("test.txt", FILE_WRITE);
				if (myFile) {
					myFile.println("- Air Humidity Program\n\n");

					myFile.println("- Bottle\t\t\t\t|\tAT(°C)\t\t|\tRAH (%)\t\t|\tST (°C)\t\t|\tSRM (%)\t\t|\tL (lx)\t\t|\tLocal Time\t\t|\tUTC Time");
					myFile.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					myFile.close(); // close the file
				}

				/*==== read sensor data & select bottle ====*/
				/*==== FLOAT POINTS! ====*/
				while (digitalRead(left) != LOW) {
					airHumidity = roundf(getAirHumidity() * 100) / 100.0;
					if (airHumidity >= 0.0 && airHumidity <= 5.0) bottlePosition = 1;
					if (airHumidity > 5.0 && airHumidity <= 10.0) bottlePosition = 2;
					if (airHumidity > 10.0 && airHumidity <= 15.0) bottlePosition = 3;
					if (airHumidity > 15.0 && airHumidity <= 20.0) bottlePosition = 4;
					if (airHumidity > 20.0 && airHumidity <= 30.0) bottlePosition = 5;
					if (airHumidity > 30.0 && airHumidity <= 40.0) bottlePosition = 6;
					if (airHumidity > 40.0 && airHumidity <= 50.0) bottlePosition = 7;
					if (airHumidity > 50.0 && airHumidity <= 60.0) bottlePosition = 8;
					if (airHumidity > 60.0 && airHumidity <= 70.0) bottlePosition = 9;
					if (airHumidity > 70.0 && airHumidity <= 80.0) bottlePosition = 10;
					if (airHumidity > 80.0 && airHumidity <= 90.0) bottlePosition = 11;
					if (airHumidity > 90.0 && airHumidity <= 100.0) bottlePosition = 12;
					else if (airHumidity < 0.0 || airHumidity > 100.0) bottlePosition = 13;

					/*==== print lcd information ====*/
					lcdBacklit();
					lcd.setCursor(0, 1);
					lcd.print("Bottle:");
					lcd.setCursor(8, 1);
					lcd.print(bottlePosition);

					//setBottle(bottlePosition);                          /*==== <- THIS NEEDS TO BE UNCOMMENTED BEFORE UPLOADED TO THE MICROCONTROLLER ====*/
					//checkBatteryLevel();                                /*==== <- BATTERY CHECK HARDWARE NOT YET IMPLEMENTED ====*/
					//checkSystemFallenDown();                            /*==== <- ACCELEROMETER NOT YET PLACED UNDER THE CONTROLLER LID ====*/

					/*==== read RTC time ====*/
					RTC.read(tm);
					
					/*==== save sensor data in SD card ====*/
					saveSensorData(bottlePosition);

					/*==== start pause loop for 5 minutes ====*/
					time = millis();
					unsigned long tempTime = 300000;
					while (millis() - time < tempTime) {
						lcdBacklit();
						if (digitalRead(left) == LOW && backlitStatus == true) {
							menu = 0;
							submenu = 0;
							tempLocation = 0;
							pressed = true;
							break;
						}
					}
				}

				/*==== print end program data ====*/
				printEndProgram();

				/*==== send SMS notification to the user ====*/
				if (activatedSMS)SMS(createMessage(systemID, "Air Humidity Program Ended"));
			}
		}

		else {
			lcdBacklit();
		}
	}
}
