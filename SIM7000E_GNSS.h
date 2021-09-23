String getUTC() {
  String UTC = "";
  String Time = "";
  String check = "";
  mySerial.println("AT+CGNSINF\r");
  do {
    mySerial.println("AT+CGNSINF\r");
    while (1) {
      if (mySerial.available()) {//provo me while nese do te ket ndonje ndryshim
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

String getLongitudePosition() {
  if (sim7000.getPosition()) {
    return sim7000.getLongitude();
  }
  return "Longitude Data Missing";
}

String getLatitudePosition() {
  if (sim7000.getPosition()) {
    return sim7000.getLatitude();
  }
  return "Latitude Data Missing";
}
