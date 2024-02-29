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

void editIntegerParameter(uint16_t x, uint16_t y, int param, int min, int max) {
    int range = max - min;
    int current_value = param;
    while (!readEnter()) {
        int next_value = readDial(range) + min;
        if (next_value != current_value) {
            char str1[4];
            sprintf(str1, "%.3i", next_value);
            tftDrawString(x, y, TXT_SEL, str1, 4);
            current_value = next_value;
        }

    tftDrawString(10, 20, TXT_SEL, "cock", 4);
    }

}



//=====[Implementations of private functions]==================================
