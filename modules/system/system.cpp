//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "tft.h"
#include "ui.h"
#include "scan.h"
#include "render.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

char *main_menu_text[4] = {"resolution", "calibration", "scan", "render"};
int main_menu_lengths[4] = {10, 11, 4, 6};

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
    tftDrawCenteredString(120, 60, TXT_HEAD, "main menu", 9);
    switch(runMenu(main_menu_text, main_menu_lengths, 4)) {
        case 0:
            resolution();
            break;
        case 1:
        case 2:
            scan();
            break;
        case 3:
            render();
            break;
    }
}

//=====[Implementations of private functions]==================================
