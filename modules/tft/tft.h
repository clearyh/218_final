//=====[#include guards - begin]===============================================

#ifndef _TFT_H_
#define _TFT_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void tftInit();
void tftSetRect(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye); //sets the rectangle from (xs, ys) to (xe, ye) for data to be written
void tftShadePixel(uint16_t x, uint16_t y, uint16_t c); // Sets the pixel at coordinates x, y to color c
void tftShadeRect(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t c); // shades a rectangle from (xs, ys) to (xe, ye), color c
void tftDrawString(uint16_t x, uint16_t y, uint16_t c, char *str, int len); //draw string at (x, y);

//=====[#include guards - end]=================================================

#endif // _TFT_H_
