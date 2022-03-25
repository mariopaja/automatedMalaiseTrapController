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


/*
    checkLightIntensity()   :   checks the light intensity
                            :   checks if thesensor is properly working
                            :   the maximal value is difficult to determine AND THEREFORE IT COULD BE REMOVED IN THE FUTURE
*/
bool checkLightIntensity(int lightIntensity) {
  if (lightIntensity >= 0 && lightIntensity <= 40000)return true;
  else return false;
}

void activateBH1750(){
  clearLCD();
  lcd.setCursor(0, 0); lcd.print("Activate Light S?");
  lcd.setCursor(0, 2); lcd.write(0);
  lcd.setCursor(2, 2); lcd.print("NO           YES");
  lcd.setCursor(19, 2); lcd.write(1);
  while(1){
    if(digitalRead(left) == LOW)break;
    if(digitalRead(right) == LOW){
        initBH1750();
      isBH1750Activated=true;
      break;
    }
  }
}