//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ui.h"
#include "tft.h"
#include "sensor.h"
#include "stepper.h"


//=====[Declaration of private defines]========================================

#define TOTAL_STEP_THETA 36000
#define TOTAL_STEP_Z 30000
#define MAX_THETA_RESOLUTION 240
#define MAX_Z_RESOLUTION 200

//=====[Declaration of private data types]=====================================

int theta_step = 0;
int z_step = 0;

int theta_resolution = 30;
int z_resolution = 30;

int theta_inc = TOTAL_STEP_THETA / theta_resolution;
int z_inc = TOTAL_STEP_Z / z_resolution;

float distanceArray[MAX_Z_RESOLUTION][MAX_THETA_RESOLUTION];

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

float getDistance(int t, int z) {
    return distanceArray[z][t];
}

void calibration() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "calibration", 11);
    tftDrawCenteredString(120, 140, TXT_SEL, "calibrate !", 11);
    tftDrawCenteredString(120, 180, TXT_NSEL, "calibrate Z", 11);
    int current_select = 0;
    while (!readBack() && !readEnter()) {
        int next_select = readDial(2);
        if (current_select == 1 && next_select == 0) {
            tftDrawCenteredString(120, 140, TXT_SEL, "calibrate !", 11);
            tftDrawCenteredString(120, 180, TXT_NSEL, "calibrate Z", 11);           
        }
        if (current_select == 0 && next_select == 1) {
            tftDrawCenteredString(120, 140, TXT_NSEL, "calibrate !", 11);
            tftDrawCenteredString(120, 180, TXT_SEL, "calibrate Z", 11);           
        }
    }
}

void resolution() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "resolution", 10);
    tftDrawString(30, 140, TXT_NSEL, "! resolution:", 12);
    tftDrawString(30, 180, TXT_NSEL, "Z resolution:", 12);
}

void scan() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan in progress", 16);
    tftDrawString(30, 140, TXT_NSEL, "! step:", 7);
    tftDrawString(30, 180, TXT_NSEL, "Z step:", 7);
    for(z_step = 0; z_step < z_resolution; z_step++) {
        char str2[5];
        sprintf(str2, "%.4i", z_step);
        tftDrawString(140, 180, TXT_SEL, str2, 4);
        for(int theta_step = 0; theta_step < theta_resolution; theta_step++) {
            char str1[5];
            sprintf(str1, "%.4i", theta_step);
            tftDrawString(140, 140, TXT_SEL, str1, 4);
            float d = readSensor();
            distanceArray[z_step][theta_step] = d;
            stepTheta(theta_inc);
        }   
        stepZ(z_inc);
    }
    tftShadeRect(30, 100, 210, 220, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan complete", 13);


}

//=====[Implementations of private functions]==================================
