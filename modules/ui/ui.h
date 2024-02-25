//=====[#include guards - begin]===============================================

#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

class Item {
    uint16_t x, y;
    char *text;
    int text_length;
    void (*function)();
    public:
    Item(uint16_t x0, uint16_t y0, char *t, int t_l, void (*func)());
    void draw();
    void select();
    void deselect();
};

//=====[Declarations (prototypes) of public functions]=========================

int readDial(int div);
bool readEnter();
bool readBack();

//=====[#include guards - end]=================================================

#endif // _UI_H_
