/*
 * Project kroll-lab-rhtp
 * Description: Firmware to measure RHT and Pressure in Lab
 * Author: David H Hagan
 * Date: October 26, 2017
 */

// Initialize some shit
#include "Adafruit_BMP085.h"
#include "LiquidCrystal.h"

Adafruit_BMP085 bmp;
LiquidCrystal lcd(D4, D6, A0, D2, D3, D5);

double TEMP, PRESSURE;
int FLAG;

// setup() runs once, when the device is first turned on.
void setup() {
  waitUntil(Particle.connected);

  // Put initialization like pinMode and begin functions here.
  FLAG = 0;
  Serial.begin(9600);

  Wire.begin();

  // Initialize the LCD Display
  lcd.begin(16, 2);

  if (!bmp.begin()){
    Serial.println("Could not start Pressure Sensor");
    FLAG = 1;
  }

  Particle.variable("TEMP", TEMP);
  Particle.variable("PRESSURE", PRESSURE);
  Particle.variable("FLAG", FLAG);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  // Set the RH and T to be variables
  TEMP = bmp.readTemperature();

  // Convert pressure from Pa to mbar
  PRESSURE = bmp.readPressure() / 100.;

  lcd.setCursor(0, 0);
  lcd.print("T = ");
  lcd.print(TEMP);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("P = ");
  lcd.print(PRESSURE);
  lcd.print(" mbar");


  delay(2000);

}
