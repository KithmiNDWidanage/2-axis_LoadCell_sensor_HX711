/*
 This code was developed based on the example provided by Nathan Seidle 
 on SparkFun Electronics Website (https://github.com/sparkfun/HX711-Load-Cell-Amplifier/tree/master/firmware)
 By: Kithmi N. D. Widanage
 University of Sussex, UK
 Date: March 21, 2025
 License: This code is public domain.
 
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 
 The provided calibration factors were obtained using SparkFun_HX711_Calibration sketch.
 These calibration factors should be changed according to your calibration results.
 The current factors were obtained for 20kg load cell using Newtons as units.
 A 10N weight was used to perform the calibration.

 Arduino Nano Every pins:
 D2 -> CLK (HX711 Board 1 - X-direction load cell)
 ~D3 -> DAT (HX711 Board 1 - X-direction load cell)
 D4 -> CLK (HX711 Board 2 - Y-direction load cell)
 ~D5 -> DAT (HX711 Board 2 - Y-direction load cell)
 5V -> VCC (Both HX711 boards)
 GND -> GND (Both HX711 boards)
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

#define calibration_factor_X 10030 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define calibration_factor_Y 10030 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_X_DOUT_PIN  3
#define LOADCELL_X_SCK_PIN  2
#define LOADCELL_Y_DOUT_PIN  5
#define LOADCELL_Y_SCK_PIN  4

HX711 sensorX;
HX711 sensorY;

void setup() {
  Serial.begin(9600);
  
  sensorX.begin(LOADCELL_X_DOUT_PIN, LOADCELL_X_SCK_PIN);
  sensorX.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  sensorX.tare();	//Assuming there is no weight on the scale at start up, reset the scale to 0

  sensorY.begin(LOADCELL_Y_DOUT_PIN, LOADCELL_Y_SCK_PIN);
  sensorY.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  sensorY.tare();	//Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {
  // The following lines will provide the output in the format [xvalue yvalue\n]
  Serial.print(sensorX.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" "); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(sensorY.get_units(), 1); //scale.get_units() returns a float
  Serial.println();
  delay(100);
}

