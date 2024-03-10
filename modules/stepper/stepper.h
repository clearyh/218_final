//=====[#include guards - begin]===============================================

#ifndef _STEPPER_H_
#define _STEPPER_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void stepperInit(); //initialization function

void stepTheta(int n); //determines movement in the rotational axis
void stepZ(int n); //determines movement in the vertical axis

//=====[#include guards - end]=================================================
 
#endif // _STEPPER_H_
