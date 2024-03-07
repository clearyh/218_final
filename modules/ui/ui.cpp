//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "tft.h"

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
    return (int) (dial.read()*div);
}

bool readEnter() {
    return enter.read();
}

bool readBack() {
    return back.read();
}

int runMenu(char **entries, int *entry_lengths, int length) {
    int current_select = 0;
    for (int i = 0; i < length; i++) {
        tftDrawCenteredString(120, 100 + 40 * i, TXT_NSEL, entries[i], entry_lengths[i]);
    }
    while (!readEnter()) {
        int next_select = readDial(length);
        if (next_select != current_select) {
            tftDrawCenteredString(120, 100 + 40 * current_select, TXT_NSEL, entries[current_select], entry_lengths[current_select]);
            tftDrawCenteredString(120, 100 + 40 * next_select, TXT_ENTR, entries[next_select], entry_lengths[next_select]);
            current_select = next_select;
        }
    }
    return current_select;
}



//=====[Implementations of private functions]==================================
