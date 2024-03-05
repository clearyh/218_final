//=====[#include guards - begin]===============================================

#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>

#define THETA_RESOLUTION 120
#define Z_RESOLUTION 100

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

float getDistance(int t, int z);

void calibration();
void resolution();
void scan();


//=====[#include guards - end]=================================================
 
#endif // _SCAN_H_
