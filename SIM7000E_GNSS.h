/*
    getUTC()    :   return UTC time
                :   GNSS must be activated in order to read the UTC
                :   AT+CGNSINF\r command requests all data of GNSS
                :   UTC is located between char 27 and 41
                :   IT MIGHT BE PROBLEMATIC IF CHARACTERS ARE MISSING FROM THE CHECK string
                :   UTC WAS TESTES ONLY IN ONE PLACE AND CHANGEING LOCATIONS COULD RESULT IN CHECK.SUBSTRING TO CHANGE
                :   I COULDNT FIND A FUNCTION AT SIM7000 LIBRARY THAT RETURNS DIRECTLY THE UTC
*/
String getUTC() {
  String UTC = "";
  String Time = "";
  String check = "";
  mySerial.println("AT+CGNSINF\r");
  do {
    mySerial.println("AT+CGNSINF\r");
    while (1) {
      if (mySerial.available()) {
        check = mySerial.readString();
        Serial.println(check);
        break;
      }
    }
    if (check.length() > 100) {
      Time = check.substring(27, 41);
      UTC = Time.substring(8, 10) + ":" + Time.substring(10, 12) + ":" + Time.substring(12) + " " + Time.substring(6, 8) + "/" + Time.substring(4, 6) + "/" + Time.substring(0, 4);
      return (UTC);
    }
    delay(2500);
  } while (1);
}

/*
    getLongitudePosition()  :   return longtidute from gps module
*/
String getLongitudePosition() {
  if (sim7000.getPosition()) {
    return sim7000.getLongitude();
  }
  return "Longitude Data Missing";
}

/*
    getLatitudePosition()   :   return latitude from gps module
*/
String getLatitudePosition() {
  if (sim7000.getPosition()) {
    return sim7000.getLatitude();
  }
  return "Latitude Data Missing";
}
