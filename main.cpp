//=====[Libraries]=============================================================


#include "tft.h"
#include "ui.h"
#include "scan.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    tftInit();
    scan();
    while (true) {
        
    }
}