//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "tft.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn dial(A0);
DigitalIn enter(D4);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================


void uiInit() {
    enter.mode(PullDown);
}


// divides the potentiometer into div sections and returns an integer for which section the wiper is in
// e.g. for div = 5, potentiometer full ccw returns 0 and full cw returns 4
int readDial(int div) {
    int ret = (int) (dial.read()*div);
    if (ret >= 0 && ret < div) return ret;
    else return div - 1;
}

bool readEnter() {
    return enter.read();
}


// function to run a text menu with multiple options and return an int that indicates which option is selected
int runMenu(char **entries, int *entry_lengths, int length) {
    int current_select = 0;
    int next_select = readDial(length);
    for (int i = 0; i < length; i++) {
        tftDrawCenteredString(120, 60 + 40 * i, TXT_NSEL, entries[i], entry_lengths[i]);
    }
    tftDrawCenteredString(120, 60 + 40 * next_select, TXT_ENTR, entries[next_select], entry_lengths[next_select]);
    while (!readEnter()) {
        next_select = readDial(length);
        if (next_select != current_select) {
            tftDrawCenteredString(120, 60 + 40 * current_select, TXT_NSEL, entries[current_select], entry_lengths[current_select]);
            tftDrawCenteredString(120, 60 + 40 * next_select, TXT_ENTR, entries[next_select], entry_lengths[next_select]);
            current_select = next_select;
        }
    }
    tftShadeRect(0, 0, 240, 320, 0x0000);
    return current_select;
    
}



//=====[Implementations of private functions]==================================
