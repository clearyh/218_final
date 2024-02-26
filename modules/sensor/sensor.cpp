//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

#define V1 0.3
#define V2 2.01
#define I1 .024
#define I2 0.155
#define M (I2 - I1)/(V2 - V1)

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn sensor(A5);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void sensorInit() {

}

float readSensor() {
    float v = sensor.read_voltage();
    float inv_dist = M * (v - V1) + I1;
    float off_dist = 1.0 / inv_dist;
    return off_dist - 0.42;
}

//=====[Implementations of private functions]==================================
