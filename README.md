3D LiDAR Scanner

Weiheng He & Harmon Cleary

3/9/24

This is the code for a 3D scanner that will make use of a LiDAR sensor and motors to create and display 3D models of real-life objects. After initializations of the scanner and display,
the ui is shown and a selection of options presents itself. During the actual scanning,  stepper motors rotate the platform in increments and use the sensor to scan and plot at each 
increment. The resulting scanned model is then shown on the display. 

Additionally to the embedded system code, python code for blender is used to turn a set of 3d points into a mesh. the code is included as the file blend.

Modules
=============================================================================
There are a total of eight modules, pc_serial_com, render, scan, sensor, stepper, system, tft, and ui. 

pc_serial_com: (Based on textbook code)
- facilitates communication between the Nucleo and serial monitors on devices.
- single public function - to send a string of a specified length to serial monitor.

render: (Written from scratch)
- transforms the array of distance points into an array of values for our display.
- render function - iterates through each measurement and converts it to a 2D coordinate in the screen space and colors the corresponding pixel
- transmit function - iterates through each measurement and converts it to 3D cartesian coordinate representing a point on the surface of the target object, then transmits this coordinate in human-readable ASCII using pc_serial_com module. 

Scan: (Written from scratch)
- uses the stepper and sensor functions to rotate the object on theta axis and lift sensor on z axis
- records sensor readings in an array as unsigned integers
- resolution function - allows the user to select a scanning resolution
- calibration function - allows the user to zero the travel of the axes
- scan function - carries out scanning, recording data in the distanceArray. the number of samples is determined by the selected resolution

Sensor: (Written from scratch)
- single function readSensor returns unsigned 16 bit integer from the AnalogIn connected to distance sensor

Stepper: (Written from scratch)
- functions to move either the theta or z axis an integer number of steps, which can be positive or negative to represent 2 directions

System: (Written from scratch)
- initiates user inputs and tft
- mainMenu function - runs the main menu, allowing user to choose the next process from 5 options: resolution, calibration, scan, render, and transmit.

tft: (Written from scratch)
- interfaces with the display
- initializes the display be sending a sequence of commands
- functions to change single pixels or rectangle regions to a single color
- functions to write strings at particular xy coordinates
- includes font.h, constant data for drawing characters on the screen (preexisting, but original)

ui: (Written from scratch)
- takes data from the user input components and calls tft module to drive interactive text menus.
- function readEnter returns boolean true when the enter button is pressed
- function readDial takes an integer argument div and returns an integer on [0, div) corresponding to the position of the potentiometer wiper
- function runMenu takes an array of pointers to character arrays, the lengths of these character arrays, and an integer length. the arrays are displayed as text menu options, and the user can use the dial to select one of the options. an integer corresponding to the selected option is returned.

Structure
=
The full structure of this device includes the following hardware peripherals and their connections to the Nucleo-F429ZI:
1. TFT_ST7789V (TFT driver chip on Adafruit 240x320 TFT display)
   - 3.3V, GND, PF12, PA5, PD15, PD14, PA7, PA6 (SPI interface with additional data/command signal and reset pin)
3. 2x MP6500 Stepper Motor Driver (on pololu breakout board)
   - 3.3V, GND, PE13, PG14, PF15, PG9, (step input and direction input for 2 boards), 5V for motor power
5. 2x Stepper Motor
   - 2 connections to each motor solenoid from driver board x 2 solenoids per motor x 2 motors = 8 connections
7. GP2Y0A41SK0F Analog output type distance measuring Sensor
   - 5V, GND, PC0 (analog output varying from ~0 to ~3.3V)
  
TESTS
=
|Test:|Subsystem:|Results:|
|:----|:----|:----|
|Full Motion Test - theta axis|Stepper Motors|Completed an exact 360° rotation consistently in 3 trials|
|Full Motion Test - Z axis|Stepper motors|Z axis has a full range of 12 cm, which is consistent across 3 trials. Carriage is able to reset to its exact starting position after each scan|
|Spatial Resolution Test - ADC|NUCLEO ADC|The smallest variation in distance distinguishable by the ADC for a surface approximately 6cm from the sensor is 0.03 mm|
|Spatial Resolution Test - Sensor signal noise|Distance sensor|A range of 2.2 cm was found in error measurements|
|Spatial Resolution Test - Sensor FOV|Distance sensor|Through testing various FOVs, a 0.125 radius FOV was found to work best at providing measurements with the least accuracy tradeoff|
|Speed Test|System|Testing on the lowest resolution of 45 x 30, the scan took 15 minutes and 55 seconds, which was slightly longer but close to the expected 14 minutes. |
|Full Functionality Test|System|After scanning a Rubix cube, the data points were successfully plotted in blender to show a 3D outline of the cube|

