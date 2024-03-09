//=====[#include guards - begin]===============================================

#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>

#define THETA_RESOLUTION_MAX 285 // max resolution (for array size)
#define Z_RESOLUTION_MAX 180

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================



//=====[Declarations (prototypes) of public functions]=========================

uint16_t getSensorReading(int t, int z);

int getZres();
int getTres();

void scan();
void resolution();
void calibration();


//=====[#include guards - end]=================================================
 
#endif // _SCAN_H_
