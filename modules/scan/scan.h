//=====[#include guards - begin]===============================================

#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>

#define THETA_RESOLUTION_MAX 296 // max resolution (for array size)
#define Z_RESOLUTION_MAX 150

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================



//=====[Declarations (prototypes) of public functions]=========================

uint16_t getSensorReading(int t, int z);

int getZres();
int getTres();

void scan();
void resolution();


//=====[#include guards - end]=================================================
 
#endif // _SCAN_H_
