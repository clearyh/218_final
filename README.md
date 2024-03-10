3D LiDAR Scanner

Weiheng He & Harmon Cleary

3/9/24

This is the code for a 3D scanner that will make use of a LiDAR sensor and motors to create and display 3D models of real-life objects. After initializations of the scanner and display,
the ui is shown and a selection of options presents itself. During the actual scanning,  stepper motors rotate the platform in increments and use the sensor to scan and plot at each 
increment. The resulting scanned model is then shown on the display. 

Modules
=============================================================================
There are a total of eight modules, pc_serial_com, render, scan, sensor, stepper, system, tft, and ui. 

pc_serial_com: (Based on textbook code)
- facilitates communication between the Nucleo and serial monitors on devices.

render: (Written from scratch)
- transforms the array of distance points into an array of values for our display.

Scan: (Written from scratch)
- activates our LiDAR sensor to detect distance.
- records the theta and z points onto an array.

Sensor: (Written from scratch)
- reads our raw sensor input to be translated into distance.

Stepper: (Written from scratch)
- slowly rotates the object's platform 360° in steps.
- will raise the sensor for each rotation until the specified scanning arc chosen by the user is achieved.

System: (Written from scratch)
- combines the rest of the modules to present a verifiable output.

tft: (Written from scratch)
- controls and handles the display outputs.
- shows the ui and its choices.

ui: (Written from scratch)
- provides the user a selection of choices upon startup.
- these inputs control what directive the system follows.

Structure
=
The full structure of this device includes the following hardware peripherals and their connections to the Nucleo-F429ZI:
1. TFT_ST7789V
   - 3.3V, GND, PF12, PA5, PD15, PD14, PA7, PA6
3. MP6500 Stepper Motor Driver
   - 3.3V, GND, PE13, PG14, PF15, PG9, connections to motors
5. Stepper Motor
   - Connections to drivers
7. GP2Y0A41SK0F Analog output type distance measuring Sensor
   - 5V, GND, PC0
  
TESTS
=
|Test:|Functionality:|Comments:|
|:----|:----|:----|
|Full Motion Test - theta axis|Stepper Motors|Completed an exact 360° rotation in 3 trials|
|Full motion test - Z axis|Stepper motors|Z axis has a full range of ~4.75 inches, which is consistent across 3 trials|
