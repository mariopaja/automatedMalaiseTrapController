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
#define PIN_TX     7                                /*  <-  declare TX pin of sim7000 module    */  
#define PIN_RX     10                               /*  <-  declare RX pin of sim7000 module    */
SoftwareSerial     mySerial(PIN_RX, PIN_TX);        /*  <-  declare the serial communication between the sim7000 and arduino mega   */
DFRobot_SIM7000    sim7000;                         /*  <-  setup serial communication between the sim7000 and arduino mega */
String phoneNumber;                                 /*  <-  declare the phone number variable    */
String mobileOperator;                              /*  <-  declare the mobile operator */
//bool sms = true;                                    
//bool gnss = true;                                   
bool activatedSIM7000E = false;                     /*  <-  declare sim7000 as non-active   */
bool activatedSMS = false;                          /*  <-  declare sms function as non-active  */
bool activatedGNSS = false;                         /*  <-  declare gnss function as non-active */


/*========== BM280 Sensor ==========*/
typedef DFRobot_BME280_IIC    BME;                  /*  <-  declare variable name of the BME280 */
BME   bme(&Wire, 0x76);                             /*  <-  declare the bme280 I2C address  */
#define SEA_LEVEL_PRESSURE    1015.0f               /*  <-  define the sea level pressure   (variable mot used) */


/*========== BH1750 Module =========*/
int BH1750address = 0x23;                           /*  <-  declare the BH1750 address  */
byte buff[2];                                       /*  <-  declare the buffer where the BH1750 saves the data*/


/*============== CSMS ==============*/
const int dry = 595;                                /*  <-  value for dry sensor    */
const int wet = 239;                                /*  <-  value for wet sensor    */
int sensorVal;                                      /*  <-  declare the sensor value variable   */


/*============ ADXL335 =============*/
const int xpin = A0;                                /*  <-  define the x pin of accelerometer  */
const int ypin = A1;                                /*  <-  define the y pin of accelerometer  */
const int zpin = A2;                                /*  <-  define the z pin of accelerometer  */


/*========== DHT22 Module ==========*/
#define DHTPIN 6                                    /*  <-  define dht22 data pin    */
#define DHTTYPE DHT22                               /*  <-  define dht model         */
DHT DHT_22(DHTPIN, DHTTYPE);                        /*  <-  Initialize DHT sensor for normal 16mhz Arduino  */


/*========= DS18B20 Sensor =========*/
#define DS18B20 9                                   /*  <-  define soil temperature data pin    */            
OneWire oneWire(DS18B20);                           /*  <-  define one wire communication   */    
DallasTemperature DS18B20sensor(&oneWire);          /*  <-  initiliaze onewire communication    */
float Celcius = 0;
float Fahrenheit = 0;


/*===== H-Bridge Motor Driver ======*/
#define motorInput_1 3                              /*  <-  define h-bridge input 1 */
#define motorInput_2 4                              /*  <-  define h-bridge input 2 */


/*========== LCD Display ===========*/
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); /*  <-  define lcd panel i2c address    */


/*===== Real-Time-Clock Module =====*/
tmElements_t tm;                                    /*  <-  define time variable    */


/*========= SD Card Module =========*/
#define Vcc_SDcard  48                              /*  <-  define vcc pin of sd card   */
#define GND_SDcard  49                              /*  <-  define gnd pin of sd card   */
#define pinCS  53                                   /*  <-  define CS pin of the sd card    */
File myFile;                                        /*  <-  define file variable    */
char c;                                             


/*============= Keypad =============*/
#define sel  22                                     /*  <-  define select  */
#define down  23                                    /*  <-  define down    */
#define up  24                                      /*  <-  define up      */
#define left  25                                    /*  <-  define left    */
#define right  26                                   /*  <-  define right   */
#define GND_buttons  27                             /*  <-  define gnd of keypad  */


/*=== Magnets & Stopping Switch ====*/
#define GND_rotor  42                               /*  <-  define gnd of the stopping mechanism sensors    */
#define switchToddle  43                            /*  <-  define switch toddle    */
#define magnet1  44                                 /*  <-  define magnet 1    */
#define magnet2  45                                 /*  <-  define magnet 2    */
#define magnet4  46                                 /*  <-  define magnet 4    */
#define magnet8  47                                 /*  <-  define magnet 8    */


/*============== Menu ==============*/
int menu = 0;                                       /*  <-  declare the main menu level */
int submenu = 0;                                    /*  <-  declare the main submenu level  */
bool pressed = true;                                /*  <-  declare as plessed to clear the lcd on the first boot   */
unsigned long backlitTime;                          /*  <-  declare the variable that counts the duration that lcd is on    */
bool backlitStatus = true;                          /*  <-  declare backlit as on during booting    */
bool restarted = true;                              /*  <-  declare restarted as true to allow saving boot data on boot */


/*========= Program Time ===========*/
int  Time[5];                                       /*  <-  declare time array to store time temporary  */
bool correctTime = false;                           /*  <-  declare correct time as false to forse config to change time    */
bool timeSaved = false;                             /*  <-  declare as false to force programs to check the correct time only once  */


/*======== Manual Program ==========*/
int nrIntervals = 1;                                /*  <-  declare the minimum number of intervals */
int tempLocation = 0;

/*  array that will contain all the program data    */
/*  array values are set to defaults, bottle=1 & minutes=15*/
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
