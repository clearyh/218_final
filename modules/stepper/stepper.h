//=====[#include guards - begin]===============================================

#ifndef _STEPPER_H_
#define _STEPPER_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void stepperInit();

void stepTheta(int n);
void stepZ(int n);

//=====[#include guards - end]=================================================
 
#endif // _STEPPER_H_
