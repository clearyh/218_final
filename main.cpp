//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "tft.h"
#include "ui.h"
#include "scan.h"
#include "stepper.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    tftInit();
    scan();
    while (true) {
    }
}