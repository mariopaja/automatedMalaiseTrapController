#include <Wire.h>               /* I2C BUS Communication */
#include <LiquidCrystal_I2C.h>  /* I2C LCD Display library */
#include <TimeLib.h>            /* Time Library */
#include <DS1307RTC.h>          /* Real Time Clock library */
#include <SPI.h>                /* SPI BUS Communication */
#include <SD.h>                 /* SD card library */
#include <EEPROM.h>             /* EEPROM Library */
#include <OneWire.h>            /* One Wire Data Communication */
#include <DHT.h>                /* DHT22 Sensor Library */
#include <DFRobot_SIM7000.h>    /* SIM7000E Module Library */
#include <DallasTemperature.h>  /* DS18B20  Sensor Library */
#include "DFRobot_BME280.h"     /* BME280 Sensor Library */
#include <math.h>


/*========= System ID ========*/
unsigned int systemID;
String programID = "";

/*========= SIM7000E Module ========*/
#define PIN_TX     7
#define PIN_RX     10
SoftwareSerial     mySerial(PIN_RX, PIN_TX);
DFRobot_SIM7000    sim7000;
String phoneNumber;
String mobileOperator;
bool sms = true;
bool gnss = true;
bool activatedSIM7000E = false;
bool activatedSMS = false;
bool activatedGNSS = false;


/*========== BM280 Sensor ==========*/
typedef DFRobot_BME280_IIC    BME;
BME   bme(&Wire, 0x76);
#define SEA_LEVEL_PRESSURE    1015.0f


/*========== BH1750 Module =========*/
int BH1750address = 0x23;
byte buff[2];


/*============== CSMS ==============*/
const int dry = 595; // value for dry sensor
const int wet = 239; // value for wet sensor
int sensorVal;


/*============ ADXL335 =============*/
const int xpin = A0;
const int ypin = A1;
const int zpin = A2;


/*========== DHT22 Module ==========*/
#define DHTPIN 6
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT DHT_22(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


/*========= DS18B20 Sensor =========*/
#define DS18B20 9
OneWire oneWire(DS18B20);
DallasTemperature DS18B20sensor(&oneWire);
float Celcius = 0;
float Fahrenheit = 0;


/*===== H-Bridge Motor Driver ======*/
#define motorInput_1 3//y input1 low (GND pin)
#define motorInput_2 4//o input2 high (5v pin)


/*========== LCD Display ===========*/
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


/*===== Real-Time-Clock Module =====*/
tmElements_t tm;


/*========= SD Card Module =========*/
#define Vcc_SDcard  48
#define GND_SDcard  49
#define pinCS  53
File myFile;
char c;


/*============= Keypad =============*/
#define sel  22
#define down  23
#define up  24
#define left  25
#define right  26
#define GND_buttons  27


/*=== Magnets & Stopping Switch ====*/
#define GND_rotor  42 //white jumper at project //1
#define switchToddle  43
#define magnet1  44
#define magnet2  45
#define magnet4  46
#define magnet8  47


/*============== Menu ==============*/
int menu = 0;
int submenu = 0;
bool pressed = true;
unsigned long backlitTime;
bool backlitStatus = true;
bool restarted = true;


/*========= Program Time ===========*/
int  Time[5];
bool correctTime = false;
bool timeSaved = false;


/*======== Manual Program ==========*/
int nrIntervals = 1;
int tempLocation = 0;
short int intervalData[] = {1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15,
                            1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15
                           };


/*========= Auto Program ===========*/
/*
   Please be sure the length of the program names are the same.
   If not add " "(blank spaces) or shorten it
*/
short int program2select = 0;
short int nrPrograms = 4;
String programs[] = {"Light Intensity "/*Program 0*/, "Soil Temperature"/*Program 1*/, "Soil Moisture   "/*Program 2*/, "Air Humidity    "/*Program 3*/};

/*======== Program 0 Data =========*/
short int Data_P0[14] = {0, 5, 10, 20, 50, 80, 100, 150, 500, 1000, 10000, 25000, 65535};
/*======== Program 1 Data =========*/
short int Data_P1[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/*======== Program 2 Data =========*/
short int Data_P2[14] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100};
/*======== Program 3 Data =========*/
short int Data_P3[14] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100};


/*========= GUI Program ===========*/
String program;


/*============ EEPROM =============*/
int machineID;
int tempID;
int eeAddress = 0;
