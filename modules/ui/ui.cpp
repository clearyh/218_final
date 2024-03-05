//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "tft.h"
#include "ui.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn dial(A0);
DigitalIn enter(D4);
DigitalIn back(D5);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================


void uiInit() {
    enter.mode(PullDown);
    back.mode(PullDown);
}

int readDial(int div) {
    float f = dial.read();
    float d = 1.0 / div;
    return (int) (f/d);
}

bool readEnter() {
    return enter.read();
}

bool readBack() {
    return back.read();
}



//=====[Implementations of private functions]==================================