void setProgramID() {
  RTC.read(tm);
  programID = "AMMOD-T" + String(systemID) + "-M-R" + return2digits(tmYearToCalendar(tm.Year)) + return2digits(tm.Month) + return2digits(tm.Day) + "-B";
}

void saveSensorData(int bottlePosition) {
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.print("- ");
    myFile.print(programID);
    if (bottlePosition == 13)myFile.print("N");
    else myFile.print(bottlePosition);
    myFile.print("\t\t|\t");
    myFile.print(getAirTemperature()); myFile.print("\t\t|\t");


    myFile.print(getAirHumidity());
    if (!checkAirHumidity())myFile.print("(E)");
    myFile.print("\t\t|\t");


    myFile.print(getSoilTemperature());
    if (!checkSoilTemperature())myFile.print("(E)");
    myFile.print("\t\t|\t");


    myFile.print(getSoilMoisture());
    if (!checkSoilMoisture())myFile.print("(E)");
    myFile.print("\t\t|\t");


    myFile.print(getLightIntensity());
    if (!checkLightIntensity())myFile.print("(E)");
    myFile.print("\t\t|\t");


    myFile.print(return2digits(tm.Hour)); myFile.print(":"); myFile.print(return2digits(tm.Minute));
    myFile.print(" ");
    myFile.print(return2digits(tm.Day)); myFile.print("/"); myFile.print(return2digits(tm.Month)); myFile.print("/"); myFile.print(return2digits(tmYearToCalendar(tm.Year))); myFile.print("\t|\t");
    if (activatedGNSS)myFile.println(getUTC());
    else myFile.println("-");
    myFile.close(); // close the file
  }
}
