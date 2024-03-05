//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "scan.h"
#include "ui.h"
#include "tft.h"
#include "sensor.h"
#include "stepper.h"


//=====[Declaration of private defines]========================================

#define TOTAL_STEP_THETA 16 * 16 * 15
#define TOTAL_STEP_Z 30000

#define THETA_INCREMENT TOTAL_STEP_THETA / THETA_RESOLUTION
#define Z_INCREMENT TOTAL_STEP_Z / Z_RESOLUTION


//=====[Declaration of private data types]=====================================

int theta_step = 0;
int z_step = 0;

int16_t distanceArray[Z_RESOLUTION][THETA_RESOLUTION];

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

float getDistance(int t, int z) {
    return distanceArray[z][t];
}

void scan() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan in progress", 16);
    tftDrawString(30, 140, TXT_NSEL, "! step:", 7);
    tftDrawString(30, 180, TXT_NSEL, "Z step:", 7);
    for(z_step = 0; z_step < Z_RESOLUTION; z_step++) {
        char str2[5];
        sprintf(str2, "%.4i", z_step);
        tftDrawString(140, 180, TXT_SEL, str2, 4);
        for(int theta_step = 0; theta_step < THETA_RESOLUTION; theta_step++) {
            char str1[5];
            sprintf(str1, "%.4i", theta_step);
            tftDrawString(140, 140, TXT_SEL, str1, 4);
            distanceArray[z_step][theta_step] = readSensor();
            stepTheta(THETA_INCREMENT);
        }   
        stepZ(Z_INCREMENT);
    }
    tftShadeRect(30, 100, 210, 220, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan complete", 13);
}

//=====[Implementations of private functions]==================================
