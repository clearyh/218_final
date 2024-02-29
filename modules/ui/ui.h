//=====[#include guards - begin]===============================================

#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================



//=====[Declarations (prototypes) of public functions]=========================

void uiInit();

int readDial(int div);
bool readEnter();
bool readBack();

void editIntegerParameter(uint16_t x, uint16_t y, int param, int min, int max);

//=====[#include guards - end]=================================================

#endif // _UI_H_
