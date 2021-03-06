/*
    activateSIM7000E()  :   asks the user if the sim7000e will be activated
                        :   by default sim7000e is not activated (set to false)
*/
void activateSIM7000E(){
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Activate SIM7000E?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
      activatedSIM7000E = true;
      break;
    }
  }
}
/*
   initSIM7000E() : Initialise SIM7000E serial
                  : Check if SIM7000E is ON (7-12V is required)
                  : Print Data on LCD display
*/
void initSIM7000E() {
  sim7000.begin(mySerial);
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Init. SIM7000E");
  if (sim7000.turnON()) {
    lcd.setCursor(0, 2); lcd.print("OK");
    delay(4000);
  }
}

/*
   initSerial() : Initialise SIM7000E Baud Rate
                : Print data on LCD Display

*/
void initSerial() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Init. Baud Rate");
  while (1) {
    if (sim7000.setBaudRate(19200)) {
      lcd.setCursor(0, 2); lcd.print("OK");
      delay(5000);
      break;
    }
    else {
      lcd.setCursor(0, 2); lcd.print("Failed");
    }
  }
  mySerial.begin(19200);
}

/*
   initPosition() : Initialise SIM7000E GNSS function
                  : Print data on LCD Display

*/
void initPosition() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Init. GNSS");
  while (1) {
    if (sim7000.initPos()) {
      lcd.setCursor(0, 2); lcd.print("OK");
      delay(5000);
      break;
    }
    else {
      lcd.setCursor(0, 2); lcd.print("Failed");
    }
  }
}

/*
   checkSerial() : Check SIM7000E serial communication
                 : Check AT command
                 : Print data on LCD Display

*/
void checkSerial() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Checking Serial");
  String check = "";
  mySerial.println("AT\r");

  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(check.length() - 4, check.length() - 2) == "OK") {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }
      else {
        lcd.setCursor(0, 2); lcd.print("Failed");
      }
    }
  }
}

/*
   checkNetwork() : Check SIM7000E Network
                  : Check connection to Mobile Operator
                  : Print data on LCD Display
*/
void checkNetwork() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Checking Network");
  String check = "";
  mySerial.println("AT+COPS?\r");
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(23, (check.length() - 11)) == mobileOperator) {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }
      else {
        lcd.setCursor(0, 2); lcd.print("Failed");
      }
    }
  }
}

/*
   enableSMS() : Enable SIM7000E SMS functionality
               : Set text messages as main SMS type
               : Print data on LCD Display
*/
void enableSMS() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Enabling SMS");
  String check = "";
  mySerial.println("AT+CMGF=1\r");
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(check.length() - 4, check.length() - 2) == "OK") {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }
      else {
        lcd.setCursor(0, 2); lcd.print("Failed");
      }
    }
  }
}

/*
    SMS()   :   sends the sms to the user
            :   the text message is input as a string   
*/
void SMS(String s) {
  String command = "AT+CMGS=" + phoneNumber;                    /*  <-  "AT+CMGS=+49xxxxxxxx is the at command that tells to the modem to send an sms to this particular phone number*/
  mySerial.println(command);                                    /*  <-  sends the command to the modem  */
  String check = "";                                            /*  <-  check is used to check the response of the modem    */
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(check.length() - 2, check.length() - 1) == ">")break;         /* <-   char ">" indicates that the command was successful and indicates that the modem ise xpecting the message */
    }
  }
  mySerial.println(s);                                          /*  <-  sends the message to the modem and then waits for the modem reply*/
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString(); break;
    }
  }
  mySerial.print(char(26));                                     /*  <- char(26) is the send command and represents \r*/
  while (1) {
    if (mySerial.available()) {//provo me while nese do te ket ndonje ndryshim
      check = mySerial.readString(); break;
    }
  }
}

/*
   setPhoneNumber(String s) :  Set phone Number to where the SMS will be sent
*/
void setPhoneNumber(String s) {
  phoneNumber = "\"" + s + "\"" + "\r";
}

/*
   setMobileOperator(String s) : Set the mobile Operator to which this device is connected
*/
void setMobileOperator(String s) {
  mobileOperator = s;
}

/*
   setPIN(String s) : Write SIM Pin in "XXXX" format
                    : Do not remove the "" quotation marks
                    : Sets SIM Pin
                    : Unlock SIM Card
*/
void setPIN(String s) {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Setting PIN");
  String pinCommand = "AT+CPIN=\"" + s + "\"" + "\r";
  mySerial.println(pinCommand);
  String check = "";
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(check.length() - 11, check.length() - 2) == "SMS Ready") {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }
    }
  }
}

/*
   checkSignalStrength() : Check Signal strength
                         : Print data on LCD Display
*/
void checkSignalStrength() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Signal Strength");
  String check = "";
  int Signal = 0;
  mySerial.println("AT+CSQ\r");
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      Signal = check.substring(15, check.length() - 11).toInt();
      if (Signal < 10) {
        lcd.setCursor(0, 2); lcd.print("Marginal");
        delay(5000);
        break;
      }
      if (Signal >= 10 && Signal < 15) {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }
      if (Signal >= 15 && Signal < 20) {
        lcd.setCursor(0, 2); lcd.print("Good");
        delay(5000);
        break;
      }
      if (Signal >= 20 && Signal <= 31) {
        lcd.setCursor(0, 2); lcd.print("Excellent");
        delay(5000);
        break;
      }
      if (Signal == 99) {
        lcd.setCursor(0, 2); lcd.print("UNKNOWN");              /*  <-  unknown signal will not allow the system to boot    */
      }
    }
  }
}

/*
   checkPosition() : Check GNSS Position
                   : Wait until Position is found
                   : Print data on LCD Display
*/
void checkPosition() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Checking Position");
  while (1) {
    if (sim7000.getPosition()) {
      lcd.setCursor(0, 2); lcd.print("OK     ");
      delay(5000);
      break;
    } else {
      lcd.setCursor(0, 2); lcd.print("Wait...");
    }
  }
}

/*
   searchNetworks() : Search available mobile operators
*/
void searchNetworks() {
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Searching Networks");
  mySerial.println("AT+COPS=?\r");
  String check = "";
  while (1) {
    if (mySerial.available()) {
      check = mySerial.readString();
      if (check.substring(3, 8) == "COPS:") {
        lcd.setCursor(0, 2); lcd.print("OK");
        delay(5000);
        break;
      }

    }
  }
}


/*
    activateSMS()   :   asks to activate SMS functionality
                    :   by default this is deactivated (set to false)
*/
void activateSMS(){
    clearLCD();
  lcd.setCursor(0, 0); lcd.print("SEND SMS?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
      activatedSMS = true;
      break;
    }
  }
}


/*
    activateGNSS()  :   asks to activate GNSS function
                    :   by default is deactivated (set to false)
*/
void activateGNSS(){
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("ACTIVATE GNSS?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
      activatedGNSS = true;
      break;
    }
  }
}

/*
    createMessage() :   returns a string containing the trap id and the message
                    :   requests the id of the trap and the string which contains the message
                    :   THIS FUNCTION IS NOT TESTED YET!
*/
String createMessage(int ID, String message) {
    return "AMMOD-T" + String(ID) + "-M " + message;
}
