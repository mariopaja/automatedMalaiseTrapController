/*
   checkDateTime() : Check if the start time is valid
*/
bool checkDateTime() {
  if (Time[4] > tmYearToCalendar(tm.Year)) return true;
  else {
    if (Time[3] > tm.Month)return true;
    if (Time[3] < tm.Month) {
      clearLCD();
      lcd.print("Please Correct Month");
      if (menu == 1)submenu = 4;
      if (menu == 2)submenu = 5;
      delay(1000);
      return false;
    }
    else {
      if (Time[2] > tm.Day)return true;
      if (Time[2] < tm.Day) {
        clearLCD();
        lcd.print("Please Correct Day");
        if (menu == 1)submenu = 3;
        if (menu == 2)submenu = 4;
        delay(1000);
        return false;
      }
      else {
        if (Time[0] > tm.Hour)return true;
        if (Time[0] < tm.Hour) {
          clearLCD();
          lcd.print("Please Correct Time");
          if (menu == 1)submenu = 1;
          if (menu == 2)submenu = 2;
          delay(1000);
          return false;
        }
        else {
          if (Time[1] >= tm.Minute)return true;
          else {
            clearLCD();
            lcd.print("Please Correct Minute");
            if (menu == 1)submenu = 2;
            if (menu == 2)submenu = 3;
            delay(1000);
            return false;
          }
        }
      }
    }
  }
}

/*
   leapYear(int years) : checks if year is leap year
*/
bool leapYear(int years) {
  if (years % 4 == 0) {
    if (Time[submenu + 1] % 100 == 0 && Time[submenu + 1] % 400 == 0) {
      return true;
    }
    return true;
  }
  return false;
}

/*
   nrIntervalCheck() : checks number of Intervals
*/
void nrIntervalCheck() {
  if (nrIntervals > 200)nrIntervals = 1;
  if (nrIntervals < 1)nrIntervals = 200;
}

/*
   checks year
*/
void YYYYcheck() {
  if (Time[4] < tmYearToCalendar(tm.Year)) Time[4] = tmYearToCalendar(tm.Year);
}

/*
   checks month
*/
void MMcheck(int x[], int y) {
  if (x[y] > 12) x[y] = 1;
  if (x[y] < 1) x[y] = 12;
}

/*
   checks date depending year and month
*/
void DDcheck() {
  if (Time[2] < 1 && (Time[3] == 1 || Time[3] == 3 || Time[3] == 5 || Time[3] == 7 || Time[3] == 8 || Time[3] == 10 || Time[3] == 12)) Time[2] = 31;
  if (Time[2] < 1 && (Time[3] == 4 || Time[3] == 6 || Time[3] == 9 || Time[3] == 11))Time[2] = 30;
  if (Time[2] < 1 && Time[3] == 2 && leapYear(Time[4]) == true)Time[2] = 29;
  if (Time[2] < 1 && Time[3] == 2 && leapYear(Time[4]) == false)Time[2] = 28;
  if (Time[2] > 31 && (Time[3] == 1 || Time[3] == 3 || Time[3] == 5 || Time[3] == 7 || Time[3] == 8 || Time[3] == 10 || Time[3] == 12)) Time[2] = 1;
  if (Time[2] > 30 && (Time[3] == 4 || Time[3] == 6 || Time[3] == 9 || Time[3] == 11))Time[2] = 1;
  if (Time[2] > 29 && Time[3] == 2 && leapYear(Time[4]) == true)Time[2] = 1;
  if (Time[2] > 28 && Time[3] == 2 && leapYear(Time[4]) == false)Time[2] = 1;
}

/*
   checks minute
*/
void mmCheck(int x[], int y) {
  if (x[y] == -1) x[y] = 59;
  if (x[y] == 60) x[y] = 0;

}

/*
   checks hour
*/
void hhCheck(int x[], int y) {
  if (x[y] == -1) x[y] = 23;
  if (x[y] == 24) x[y] = 0;
}

void tempIDcheck() {
  if (tempID < 1) tempID = 99;
  if (tempID > 99)tempID = 1;
}

void programCheck() {
  if (program2select < 0) program2select = (nrPrograms - 1);
  if (program2select > (nrPrograms - 1)) program2select = 0;
}
