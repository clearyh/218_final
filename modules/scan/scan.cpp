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

#define TOTAL_STEP_THETA 2565
#define TOTAL_STEP_Z 7695


//=====[Declaration of private data types]=====================================

uint16_t distanceArray[Z_RESOLUTION_MAX][THETA_RESOLUTION_MAX];

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int theta_inc = TOTAL_STEP_THETA / THETA_RESOLUTION_MAX;
int z_inc = TOTAL_STEP_Z / Z_RESOLUTION_MAX;

int t_res = 10; // actual resolution
int z_res = 1;

char *resolution_menu_text[4] = {"45 x 30", "95 x 60", "171 x 90", "285 x 180"};
int resolution_menu_lengths[4] = {7, 7, 8, 9};

//=====[Declarations (prototypes) of private functions]========================

static void updateIncrement();

//=====[Implementations of public functions]===================================

void scan() {
    updateIncrement();
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan in progress", 16);
    tftDrawString(30, 140, TXT_NSEL, "! step:", 7);
    tftDrawString(30, 180, TXT_NSEL, "Z step:", 7);
    for(int z_step = 0; z_step < z_res; z_step++) {
        char str2[5];
        sprintf(str2, "%.4i", z_step);
        tftDrawString(140, 180, TXT_SEL, str2, 4);
        for(int theta_step = 0; theta_step < t_res; theta_step++) {
            char str1[5];
            sprintf(str1, "%.4i", theta_step);
            tftDrawString(140, 140, TXT_SEL, str1, 4);
            distanceArray[z_step][theta_step] = readSensor();
            char float_string[6];
            sprintf(float_string, "%.3f", getDistance(z_step, theta_step));
            uartWriteString(float_string, 7);
            stepTheta(theta_inc);
        }
        stepZ(z_inc);
    }
    tftShadeRect(30, 100, 210, 220, 0x0000);
    tftDrawCenteredString(120, 100, TXT_HEAD, "scan complete", 13);
    stepZ(-TOTAL_STEP_Z);
    mainMenu();
}

void resolution() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 20, TXT_HEAD, "set resolution", 14);
    switch(runMenu(resolution_menu_text, resolution_menu_lengths, 4)) {
        case 0:
            t_res = 45;
            z_res = 30;
            break;
        case 1:
            t_res = 95;
            z_res = 60;
            break;
        case 2:
            t_res = 171;
            z_res = 90;
            break;
        case 3:
        default:
            t_res = 285;
            z_res = 180;
            break;
    }
    updateIncrement();
    mainMenu();
}

void calibration() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
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
    mainMenu();
}

int getTres() {
    return t_res;
}

int getZres() {
    return z_res;
}

uint16_t getSensorReading(int t, int z) {
    return distanceArray[z][t];
}

//=====[Implementations of private functions]==================================

static void updateIncrement() {
    theta_inc = TOTAL_STEP_THETA / t_res;
    z_inc = TOTAL_STEP_Z / z_res;
}