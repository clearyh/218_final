//=====[Libraries]=============================================================

#include "mbed.h" //including the basic libraries
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//theta is the rotational axis, z is the vertical axis
DigitalOut ThetaDir(D0); //theta direction
DigitalOut ZDir(D1); //z direction
DigitalOut ThetaStep(D2); //theta step, 
DigitalOut ZStep(D3); //z step

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void stepperInit() { //initialization function for our outputs
    ThetaDir.write(true);
    ZDir.write(true);
    ThetaStep.write(false);
    ZStep.write(false);
}

void stepTheta(int n) { //n is number of steps, positive/negative will determine direction
    if (n < 0) {
        ThetaDir.write(false); 
        n = 0 - n;
    }
    else {
        ThetaDir.write(true);
    }
    for(int i = 0; i < n; i++) {
        ThetaStep.write(true);
        wait_us(5000);
        ThetaStep.write(false);
        wait_us(5000);
    }
}

void stepZ(int n) { //n is number of steps, positive/negative will determine direction
    if (n < 0) {
        ZDir.write(false); 
        n = 0 - n;
    }
    else {
        ZDir.write(true);
    }
    for(int i = 0; i < n; i++) {
        ZStep.write(true);
        wait_us(1000);
        ZStep.write(false);
        wait_us(1000);
    }
}

//=====[Implementations of private functions]==================================
