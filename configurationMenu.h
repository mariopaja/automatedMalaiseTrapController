#include "config.h"

void configurationMenu() {
  if (submenu == 0) configMenu();
  if (submenu == 1) setID();
  if (submenu == 2) SetHour();
  if (submenu == 3) SetMinute();
  if (submenu == 4) SetDate();
  if (submenu == 5) SetMonth();
  if (submenu == 6) SetYear();
}
