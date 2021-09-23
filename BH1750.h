/*
    BH1750_Init(int address): Initialise BH1750
*/

void initBH1750() {
  Wire.beginTransmission(BH1750address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}

/*
    readBH1750(int address): Start 1 Wire Data Transmition
                           : Request Data
                           : Save Bytes in Buffer
                           : Count number of received Bytes
                           : return number of Bytes
*/
int readBH1750(int address) {
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  return i;
}



/*
    getLightIntensity() : Read Byte Data from Buffer
                        : Return the value
*/
int getLightIntensity() {
  int i;
  uint16_t val = 0;
  delay(200);
  if (2 == readBH1750(BH1750address)) {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
    return val;
  }
  return 0;
}



bool checkLightIntensity() {
  if (getLightIntensity() >= 0 && getLightIntensity() <= 400)return true;
  else return false;
}
