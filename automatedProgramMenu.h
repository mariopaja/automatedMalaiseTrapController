#include "automatedProgram.h"

void automatedProgramMenu() {
  if (submenu == 0) automatedProgram();
  if (submenu == 1) programSelector();
  if (submenu == 2) setStartHour();
  if (submenu == 3) setStartMinute();
  if (submenu == 4) setStartDay();
  if (submenu == 5) setStartMonth();
  if (submenu == 6) setStartYear();
  if (submenu == 7) startProgram();
}
