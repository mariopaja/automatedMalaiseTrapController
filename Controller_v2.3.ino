#include <avr/power.h>
#include <avr/sleep.h>
/*============== Main Declarations ================*/
#include "header.h"                   // Libraries, Declarations & Gloval variables
#include "SIM7000E_GNSS.h"            // SIM7000E Module UTC Time funtion
#include "controllerSetup.h"          // Pin Declarations & General Functions
#include "checkData.h"                // Checking Functions
/*=============== Sensor & Modules ================*/
#include "BH1750.h"                   // Light sensor
#include "DS18B20.h"                  // Soil Temperature
#include "DHT22.h"                    // Air Temperature & Humidity sensor
#include "CSMS.h"                     // Capacitive Soil Moisure Sensor
#include "SIM7000E.h"                 // SIM7000E Module GPRS + GNSS functions
#include "SIM7000E_BME280.h"          // SIM7000E BME280 sensor functions
#include "ADXL335.h"                  // Accelerometer
#include "logFile.h"
/*====================== Menu =====================*/
#include "programStartTime.h"         // Program Start Time Functions
#include "welcomeMenu.h"              // Welcome Menu Navigation Levels
#include "manualProgramMenu.h"        // Manual Program Menu Navigation Levels
#include "automatedProgramMenu.h"     // Automated Program Menu Navigation Levels
#include "configurationMenu.h"        // Configuration Menu Navigation Levels        
#include "informationMenu.h"          // Information Menu Navigation Levels
/*=========== Serial Communication GUI ============*/
#include "arduinoGUI.h"
/*============ Battery Level Checker ==============*/
#include "batteryChecker.h"




/*=========== First Time Declarations ============*/
void setup() {

  disable_unusedComponents();
  //slowArduinoDown();
  turnOFF_analogPins();
  turnOFF_digitalPins();
  /*=========== Serial Declaration ============*/
  Serial.begin(9600);
  while (!Serial);
  turnOffLED();                                             /*  <-  Turn off pin 13 which is responsinble to the led*/

  /*=========== Set System Parameters ============*/
  setSystemID(1586);                                        /*  <-  The system ID is an integer. Only write the ID number and no extra characters */
  setPhoneNumber("+4915223605953");                         /*  <-  the receiver's phone number must contain the country code. Write the phone number inside the "" */
  setMobileOperator("Dataport"); /*vodafone.de...*/         /*  <-  The name of the operator can be found from the AT-command code. Write the operator name as it appears in AT-commads*/

  /*=========== Keypad Declaration ============*/
  /*========== See controllerSetup.h ==========*/
  buttonMode();

  /*========= LCD Display Declaration =========*/
  /*========== See controllerSetup.h ==========*/
  LCD();

  /*========== H-Bridge Declaration ===========*/
  /*========== See controllerSetup.h ==========*/
  rotorDriver();
  rotorPosition();

  /*========== SIM7000E Declaration ===========*/
  /*============= See SIM7000E.h ==============*/
  //activateSIM7000E();                             /*==== <- UNCOMMENT TO ACTIVATE THE SIM CARD FUNCTIONALITY ====*/
  if (activatedSIM7000E) {
    initSIM7000E();
    initSerial();
    checkSerial();
    activateSMS();
    if (activatedSMS) {
      setPIN("5000");
      searchNetworks();
      checkNetwork();
      checkSignalStrength();
      enableSMS();
    }
    activateGNSS();
    if (activatedGNSS) {
      initPosition();
      checkPosition();
    }
    /*=========== BME280 Declaration ============*/
    /*======== See SIM7000E_BME280.h ============*/
    initBME();                                      
  }
  /*=========== DS18B20 Declaration ============*/
  /*============= See DS18B20.h ================*/
  activateDS18B20();                                /*==== <- ACTIVATES THE SOIL TEMP SENSOR ====*/
                               

  /*============= DHT22 Declaration ============*/
  /*=============== See DHT22.h ================*/
  activateDHT22();                                   /*==== <- ACTIVATES THE AIR SENSOR  ====*/

  /*============ BH1750 Declaration ============*/
  /*================ See BH1750.h ==============*/
  activateBH1750();                                 /*==== <- ACTIVATES THE LIGHT SENSOR ====*/

  /*============ CSMS Declaration ============*/
  /*================ See CSMS.h ==============*/
  activateCSMS();                                   /*==== <- ACTIVATES THE SOIL MOIST SENSOR ====*/


  /*=========== SD Card Declaration ============*/
  /*=========== See controllerSetup.h ==========*/
  sdCard();

  /*======= First Time Boot Declarations =======*/
  /*=========== See controllerSetup.h ==========*/
  rebootedSystem();
  backlitTime = millis();
}

/*================= Main Program ==================*/
void loop() {
  RTC.read(tm);                           // Read Time From RTC
  gui();                                  // See arduinoGUI.h
  lcdBacklit();                           // See controllerSetup.h

  /* Commented because the sensor is not put in place */
  //checkSystemFallenDown();                // See ADXL335.h

  checkSystemTemperature();               // See SIM7000E_BME280.h
  checkSystemHumidity();                  // See SIM7000E_BME280.h
  
  /* Commented because the voltage divider is not implemented */
  //checkBatteryLevel();                    // See controllerSetup.h

  if (menu == 0) welcomeMenu();           // See welcomeMenu.h
  if (menu == 1) manualProgramMenu();     // See manualProgramMenu.h
  if (menu == 2) automatedProgramMenu();  // See automatedProgramMenu.h
  if (menu == 3) configurationMenu();     // See configurationMenu.h
  if (menu == 4) informationMenu();       // See infomationMenu.h
}
