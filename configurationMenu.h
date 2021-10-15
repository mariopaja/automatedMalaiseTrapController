#include "config.h"

void configurationMenu() {
  if (submenu == 0) configMenu();
  if (submenu == 1) SetHour();
  if (submenu == 2) SetMinute();
  if (submenu == 3) SetDate();
  if (submenu == 4) SetMonth();
  if (submenu == 5) SetYear();
}
