#include "info.h"

void informationMenu() {
  if (submenu == 0) infoMenu();
  if (submenu == 1) showID();
  if (submenu == 2) showAirTemp();
  if (submenu == 3) showAirHum();
  if (submenu == 4) showSoilTemp();
  if (submenu == 5) showSoilMoist();
  if (submenu == 6) showLightInt();
  if (submenu == 7) showSysTemp();
  if (submenu == 8) showSysHum();
}
