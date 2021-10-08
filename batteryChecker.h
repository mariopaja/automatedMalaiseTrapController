/*
* checkBatteryLevel() checks the battery level
* Sends a SMS notification to the user if the battery is below a certain level
*/
void checkBatteryLevel() {
  //135K Ohm & 270K Ohm Resistors are needed
  if ((analogRead(A3) * (5.00 / 1023.00) * 3) < 10.0) {
    if (activatedSMS)SMS(createMessage(systemID, "Low Battery"));
  }
}
