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
    if(isDHT22Activated==true)myFile.print(getAirTemperature()); 
    else myFile.print("-");
    myFile.print("\t\t|\t");         /*  <-  print air temperature   */

    if(isDHT22Activated==true){
        float airHumidity = getAirHumidity();
    myFile.print(airHumidity);                                          /*  <-  print air humidity  */
    if (!checkAirHumidity(airHumidity))myFile.print("(E)");             /*  <-  check air humidity value    */
    }
    else myFile.print("-");
    myFile.print("\t\t|\t");

    if(isDS18B20Activated==true){
        float soilTemperature = getSoilTemperature();
    myFile.print(soilTemperature);                                      /*  <-  print soil temperature  */
    if (!checkSoilTemperature(soilTemperature))myFile.print("(E)");     /*  <-  check soil temperature value    */
    }
    else myFile.print("-");
    myFile.print("\t\t|\t");

    if(isCSMSActivated==true){
        int soilMoisture = getSoilMoisture();
    myFile.print(soilMoisture);                                         /*  <-  print soil moisture */
    if (!checkSoilMoisture(soilMoisture))myFile.print("(E)");           /*  <-  check soil moisture value   */
    }
    else myFile.print("-");
    myFile.print("\t\t|\t");

    if(isBH1750Activated==true){
int lightIntensity = getLightIntensity();
    myFile.print(lightIntensity);                                       /*  <-  print light intensity   */ 
    if (!checkLightIntensity(lightIntensity))myFile.print("(E)");       /*  <-  check light intensity value */
    }
    else myFile.print("-");
    myFile.print("\t\t|\t");


    myFile.print(return2digits(tm.Hour)); myFile.print(":"); myFile.print(return2digits(tm.Minute));
    myFile.print(" ");
    myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.print(return2digits(tmYearToCalendar(tm.Year))); myFile.print("\t|\t");

    if (activatedGNSS)myFile.println(getUTC());
    else myFile.println("-");

    myFile.close(); // close the file
  }
}
