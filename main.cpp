//=====[Libraries]=============================================================

#include "tft.h"
#include "scan.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    tftInit();
    tftShadeRect(0, 0, 240, 320, 0xFFFF);
    //scan();
    while (true) {
        
    }
}