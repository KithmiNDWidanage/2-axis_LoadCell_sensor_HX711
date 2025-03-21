# 2-axis_LoadCell_sensor_HX711
This repository includes the codes for a load cell-based 2-axis force sensor made using two 20kg strain gauge load cells combined with HX711 SparkFun Load Cell Amplifiers. The load cell data is read and printed to the Serial Port using an Arduino microcontroller.  This data is then read by a C++ program on Windows for further processing.

This sensor was originally developed to be used with Kinova Gen3 7DOF robot fixed at its end effector as a means of measuring the interaction force from a human guiding the robot in the x-y plane. The CAD files are created considering this requirement.

## Components:
This is tested with the following components:
- 2 x [Strain Gauge Load Cell - 4 Wires - 20Kg](https://thepihut.com/products/adafruit-strain-gauge-load-cell-4-wires-20kg?variant=32310617505854)
- 2 x [HX711 SparkFun Load Cell Amplifier](https://thepihut.com/products/sparkfun-load-cell-amplifier-hx711?variant=39732609908931)
- 1 x [Arduino Nano Every](https://store.arduino.cc/products/arduino-nano-every?srsltid=AfmBOoohmKPpRmF4gHxoX8Kwd7G4INoyuFBcax5I-CZxypbzW7EKvUTV) (Any suitable microcontroller would work, but the provided code, pin numbers, and CAD files are designed for this specific microcontroller)
- A known weight for calibration (1 kg mass was used here)
- 3D printed components (provided in the zip file named "CAD Files")
- Wires as required
- a USB-A to Micro USB cable (to connect the Arduino Nano Every to the PC)

## Information about the codes
These codes were tested on Windows 10. Arduino code was compiled and uploaded with Arduino IDE 2.3.4 and C++ code was compiled on GCC using MinGW64 5.4 toolchain.

For the Arduino code, the [HX711 Arduino Library by Bogdan Necula](https://github.com/bogde/HX711) was used. The Arduino code was modified from the example provided in [SparkFun HX711-Load-Cell-Amplifier repository](https://github.com/sparkfun/HX711-Load-Cell-Amplifier/tree/master). The calibration should be done using the [SparkFun_HX711_Calibration](https://github.com/sparkfun/HX711-Load-Cell-Amplifier/tree/master/firmware/SparkFun_HX711_Calibration) for each sensor and the calibration data should be recorded based on that. This Arduino code will write data into the serial port in the baud rate specified in the code.

For the C++ code, sample codes from [learn.microsoft.com](https://learn.microsoft.com/en-us/previous-versions/ff802693(v=msdn.10)?redirectedfrom=MSDN#reading-and-writing) were modified to read and process the data from the Serial port. The correct port to which the Arduino microcontroller is writing the data should be specified within the C++ code to successfully read the data. The provided code includes the configuration and reading of the Serial port communication. 
