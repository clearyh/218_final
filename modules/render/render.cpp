//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

#define VREF 3.3
#define V1 0.3
#define V2 2.01
#define I1 .024
#define I2 0.155
#define M (I2 - I1)/(V2 - V1)
#define R_SCANNER 20
#define SENSOR_ANGLE 30

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static float getDistance(uint16_t sensor_reading);
static void renderPoint(int tstep, int zstep);

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

static float getDistance(uint16_t sensor_reading) {
    float voltage = VREF * (1.0 * sensor_reading / UINT16_MAX);
    float inverse = (voltage - V1) * M + I1;
    float ret = (1.0 / inverse) - 0.42;
    return ret;
}
