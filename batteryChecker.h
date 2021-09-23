void checkBatteryLevel() {
  //135K Ohm & 270K Ohm Resistors are needed
  if ((analogRead(A3) * (5.00 / 1023.00) * 3) < double(10)) {
    SMS("Low Battery");
  }
}
