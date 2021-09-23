#include "manualProgram.h"

void manualProgramMenu() {
  if (submenu == 0) manualProgram();
  if (submenu == 1) setStartHour();
  if (submenu == 2) setStartMinute();
  if (submenu == 3) setStartDay();
  if (submenu == 4) setStartMonth();
  if (submenu == 5) setStartYear();
  if (submenu == 6) intervals();
  if (submenu == 7) configureIntervals();
  if (submenu == 8) startIntervals();
}
