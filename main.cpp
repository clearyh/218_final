//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "system.h"
#include "scan.h"
#include "stepper.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    systemInit();
    mainMenu();
    while (true) {
    }
}