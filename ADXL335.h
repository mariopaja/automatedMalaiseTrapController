/*
  getX() : Reads A0 Pin
         : Maps A0 value
         : Simplifies the value
         : Returns the rounded value as Integer
*/
int getX() {
  int xvalue = analogRead(xpin); //read from xpin
  int x = map(xvalue, 202, 300, -100, 100);
  float xg = (float)x / 100.0;
  return round(xg);
}

/*
  getY() : Reads A1 Pin
         : Maps A1 value
         : Simplifies the value
         : Returns the rounded value as Integer
*/
int getY() {
  int yvalue = analogRead(ypin); //read from xpin
  int y = map(yvalue, 195, 295, -100, 100);
  float yg = (float)y / 100.0;
  return round(yg);
}

/*
  getZ() : Reads A2 Pin
         : Maps A2 value
         : Simplifies the value
         : Returns the rounded value as Integer
*/
int getZ() {
  int zvalue = analogRead(zpin); //read from xpin
  int z = map(zvalue, 216, 316, -100, 100);
  float zg = (float)z / 100.0;
  return round(zg);
}

/*
  Standing positions : x -> 0
                     : y -> 0
                     : z -> 1
                     : true -> System has fallen down
                     : false -> System is in the right position

  If system has fallen : Information saved on log.txt
                       : SMS notification
                       : Program aborts
                       : System freezes
*/
void checkSystemFallenDown() {
  if (getX() != 0 | getY() != 0 || getZ() != 1) {
    if (activatedSIM7000E)SMS("System has fallen down");
    if (myFile) {
      myFile.println("# System Has Fallen");
      myFile.println("# Sending Error SMS");
      myFile.println("# Aborting All Tasks");
      myFile.close(); // close the file
    }
    while (1) {}
  }
}
