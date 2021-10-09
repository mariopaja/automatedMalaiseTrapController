/*
* checkBatteryLevel() checks the battery level
* Sends a SMS notification to the user if the battery is below a certain level
* 135K Ohm & 270K Ohm Resistors
* 10.0 is the minimum operation voltage of the system
* should be a bit higher than the cut off voltage of the solar charge controller
*/
void checkBatteryLevel() {
  if ((analogRead(A3) * (5.00 / 1023.00) * 3) < 10.0) {
    if (activatedSMS)SMS(createMessage(systemID, "Low Battery"));
  }
}
