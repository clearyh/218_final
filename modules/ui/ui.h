//=====[#include guards - begin]===============================================

#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================



//=====[Declarations (prototypes) of public functions]=========================

void uiInit();

int readDial(int div); // functions to read the 3 user inputs
bool readEnter();

int runMenu(char **entries, int *entry_lengths, int length); 


//=====[#include guards - end]=================================================

#endif // _UI_H_
