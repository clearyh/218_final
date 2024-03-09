//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "tft.h"
#include "ui.h"
#include "scan.h"
#include "render.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

char *main_menu_text[5] = {"resolution", "calibration", "scan", "render", "transmit"};
int main_menu_lengths[5] = {10, 11, 4, 6, 8};

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void systemInit() {
    tftInit();
    uiInit();
}

void mainMenu() {
    tftShadeRect(0, 0, 240, 320, 0x0000);
    tftDrawCenteredString(120, 20, TXT_HEAD, "main menu", 9);
    switch(runMenu(main_menu_text, main_menu_lengths, 5)) {
        case 0:
            resolution();
            break;
        case 1:
            calibration();
            break;
        case 2:
            scan();
            break;
        case 3:
            render();
            break;
        case 4:
            transmit();
            break;
    }
}

//=====[Implementations of private functions]==================================
