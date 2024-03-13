//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "render.h"
#include "scan.h"
#include "ui.h"
#include "tft.h"
#include "sensor.h"
#include "stepper.h"
#include "system.h"
#include "pc_serial_com.h"


//=====[Declaration of private defines]========================================

#define TOTAL_STEP_THETA 2565  // total number of stepper motor steps for 360degree rotation
#define TOTAL_STEP_Z 7695 // total number of stepper motor steps for full range of z axis


//=====[Declaration of private data types]=====================================

uint16_t distanceArray[Z_RESOLUTION_MAX][THETA_RESOLUTION_MAX]; //array containing raw AnalogIn data for each sensor position

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int theta_inc = TOTAL_STEP_THETA / THETA_RESOLUTION_MAX; //steps per increment theta
int z_inc = TOTAL_STEP_Z / Z_RESOLUTION_MAX; // steps per increment Z

int t_res = 15; // actual resolution
int z_res = 15;

//data for resolution menu
char *resolution_menu_text[5] = {"15 x 15", "45 x 27", "95 x 57", "171 x 90", "285 x 171"};
int resolution_menu_lengths[5] = {7, 7, 7, 8, 9};


//=====[Declarations (prototypes) of private functions]========================

static void updateIncrement();

//=====[Implementations of public functions]===================================


//scan function
void scan() {
    updateIncrement();
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan in progress", 16); // preparing tft readout
    tftDrawString(30, 140, TXT_NSEL, "! step:", 7);
    tftDrawString(30, 180, TXT_NSEL, "Z step:", 7);
    for(int z_step = 0; z_step < z_res; z_step++) { //iterating through each Z value
        char str2[5];
        sprintf(str2, "%.4i", z_step);
        tftDrawString(140, 180, TXT_SEL, str2, 4);
        for(int theta_step = 0; theta_step < t_res; theta_step++) { // iterating through each theta value
            char str1[5];
            sprintf(str1, "%.4i", theta_step);
            tftDrawString(140, 140, TXT_SEL, str1, 4);
            distanceArray[z_step][theta_step] = readSensor(); // store read sensor value in the array
    
            char float_string[6];
            sprintf(float_string, "%.3f", getDistance(theta_step, z_step));
            uartWriteString(float_string, 6);
            uartWriteString("\n", 1);

            stepTheta(theta_inc);
        }
        stepZ(z_inc);
    }
    tftShadeRect(30, 100, 210, 220, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan complete", 13); // tft readout
    stepZ(-TOTAL_STEP_Z); // return z axis carriage to home
    tftShadeRect(0, 100, 240, 220, 0x0000);
    mainMenu();
}

//function to allow the user to select scanning resolution
void resolution() {
    tftDrawCenteredString(120, 20, TXT_HEAD, "set resolution", 14);
    switch(runMenu(resolution_menu_text, resolution_menu_lengths, 5)) {
        case 0:
            t_res = 15;
            z_res = 15;
        case 1:
            t_res = 45;
            z_res = 27;
            break;
        case 2:
            t_res = 95;
            z_res = 57;
            break;
        case 3:
            t_res = 171;
            z_res = 95;
            break;
        case 4:
        default:
            t_res = 285;
            z_res = 171;
            break;
    }
    tftShadeRect(0, 20, 240, 220, 0x0000);
    mainMenu();
}


//function to allow the user to move both axes and set a home point
void calibration() {
    tftDrawCenteredString(120, 100, TXT_HEAD, "calibrate Z axis", 16);
    while (!readEnter()) {
        switch (readDial(3)) {
            case 0:
                stepZ(-10);
                wait_us(10);
                break;
            case 1:
                wait_us(10);
                break;
            case 2:
                stepZ(10);
                wait_us(10);
                break;
        }
    }
    tftDrawCenteredString(120, 100, TXT_HEAD, "calibrate ! axis", 16);
    while (!readEnter()) {
        switch (readDial(3)) {
            case 0:
                stepTheta(-10);
                delay(1);
                break;
            case 1:
                delay(1);
                break;
            case 2:
                stepTheta(10);
                delay(1);
                break;
        }
    }
    tftShadeRect(0, 100, 240, 140, 0x0000);
    mainMenu();
}

//returns current T resolution
int getTres() {
    return t_res;
}

//returns current Z resolution
int getZres() {
    return z_res;
}

// fetches raw sensor AnalogIn data from the array for the render function
uint16_t getSensorReading(int t, int z) {
    return distanceArray[z][t];
}

//=====[Implementations of private functions]==================================


// updates the z and theta increment when resolution is changed
static void updateIncrement() {
    theta_inc = TOTAL_STEP_THETA / t_res;
    z_inc = TOTAL_STEP_Z / z_res;
}