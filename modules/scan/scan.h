//=====[#include guards - begin]===============================================

#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>

#define THETA_RESOLUTION 148
#define Z_RESOLUTION 2

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

uint16_t getSensorReading(int t, int z);

void scan();


//=====[#include guards - end]=================================================
 
#endif // _SCAN_H_
