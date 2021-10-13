/*
    setProgramID()  :   creates the program ID string AMMOD-T-M-RYYYYMMDD-B
*/
void setProgramID() {
  RTC.read(tm);
  programID = "AMMOD-T" + String(systemID) + "-M-R" + return2digits(tmYearToCalendar(tm.Year)) + return2digits(tm.Month) + return2digits(tm.Day) + "-B";
}

/*
    saveSensorData()    :   saves the sensor data on the SD card
                        :   request the bottle position to fill the programID
                        :   sensor data are read and then checked if they comply to the operation condtions
*/
void saveSensorData(int bottlePosition) {
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.print("- ");
    myFile.print(programID);
    if (bottlePosition == 13)myFile.print("N");
    else myFile.print(bottlePosition);


    myFile.print("\t\t|\t");
    myFile.print(getAirTemperature()); myFile.print("\t\t|\t");         /*  <-  print air temperature   */

    float airHumidity = getAirHumidity();
    myFile.print(airHumidity);                                          /*  <-  print air humidity  */
    if (!checkAirHumidity(airHumidity))myFile.print("(E)");             /*  <-  check air humidity value    */
    myFile.print("\t\t|\t");


    myFile.print(getSoilTemperature());                                 /*  <-  print soil temperature  */ 
    if (!checkSoilTemperature())myFile.print("(E)");                    /*  <-  check soil temperature value    */
    myFile.print("\t\t|\t");


    myFile.print(getSoilMoisture());                                    /*  <-  print soil moisture */ 
    if (!checkSoilMoisture())myFile.print("(E)");                       /*  <-  check soil moisture value   */
    myFile.print("\t\t|\t");


    myFile.print(getLightIntensity());                                  /*  <-  print light intensity   */ 
    if (!checkLightIntensity())myFile.print("(E)");                     /*  <-  check light intensity value */
    myFile.print("\t\t|\t");


    myFile.print(return2digits(tm.Hour)); myFile.print(":"); myFile.print(return2digits(tm.Minute));
    myFile.print(" ");
    myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.print(return2digits(tmYearToCalendar(tm.Year))); myFile.print("\t|\t");
    if (activatedGNSS)myFile.println(getUTC());
    else myFile.println("-");
    myFile.close(); // close the file
  }
}
