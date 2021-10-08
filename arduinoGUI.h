/*
   gui() : Check Serial for incomming Data
         : Read incomming Data as String File
         : First char of incomming String indicates program
            - A : Start Automated Program
                : Save Request on logData
                : Save Data on Local Variables -> starting time, selected program
                : Format (A;hh;mm;DD;MM;YYYY;P)

            - N : Read System Info
                : Save Request on logData
                : Send System Info as String via Serial Communication

            - S : Start Manual Program
                : Save request on logData
                : Save Data on Local Variables -> starting time, tunr interval data from strings to integers and then save to local memory
                : Format (S;hh;mm;DD;YYYY;B,D;B,D.....) -> B is integer 1 to 13 and D is the interval duration in minutes

            - R : Change RTC Time

*/
void gui() {
  if (Serial.available()) {
    program = Serial.readString();
    c = program.charAt(0);
    /*===========================Start Switch Case==============================*/
    switch (c) {
      /*===========================Automated Program==============================*/
      case'A':
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.println("# New Automated Program Received\n");
          myFile.close();
        }
        program.remove(0, 1);
        Time[0] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[1] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[2] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[3] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[4] = program.substring(0, 4).toInt(); program.remove(0, 5);
        program2select = program.toInt();
        menu = 2;
        submenu = 7;
        pressed = true;
      /*===========================Read Info==============================*/
      case 'N':
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.println("# User Requested System Information Read\n");
          myFile.close(); // close the file
        }
        delay(100);
        Serial.println(systemID); delay(100);
        Serial.println(getAirTemperature()); delay(100);
        Serial.println(getAirHumidity()); delay(100);
        Serial.println(getSoilTemperature()); delay(100);
        Serial.println(getSoilMoisture()); delay(100);
        Serial.println(getLightIntensity());
        break;
      /*===========================Change RTC Time==============================*/
      case 'R':
        program.remove(0, 1);
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.println("# User Updated Time\n");
          myFile.close(); // close the file
        }
        tm.Hour = program.substring(0, 2).toInt(); program.remove(0, 3);
        tm.Minute = program.substring(0, 2).toInt(); program.remove(0, 3);
        tm.Second = program.substring(0, 2).toInt(); program.remove(0, 3);
        tm.Day = program.substring(0, 2).toInt(); program.remove(0, 3);
        tm.Month = program.substring(0, 2).toInt(); program.remove(0, 3);
        tm.Year = CalendarYrToTm(program.substring(0, 4).toInt());
        RTC.write(tm);
        break;
      /*===========================Start Manual Program==============================*/
      case 'S':
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.println("# New Program Received\n");
          myFile.close();
        }
        program.remove(0, 1);
        Time[0] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[1] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[2] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[3] = program.substring(0, 2).toInt(); program.remove(0, 3);
        Time[4] = program.substring(0, 4).toInt(); program.remove(0, 5);
        int start = 0;
        int cnt = 0;
        nrIntervals = 0;
        for (int i = 0; i < program.length(); i++) {
          if (program.charAt(i) == ',') {
            intervalData[cnt++] = int(program.substring(start, i).toInt());
            start = i + 1;
          }
          if (program.charAt(i) == ';') {

            intervalData[cnt++] = int(program.substring(start, i).toInt());
            start = i + 1;
            nrIntervals++;
          }
        }
        menu = 1;
        submenu = 8;
        pressed = true;
        break;
    }
  }
}
