//=====[#include guards - begin]===============================================

#ifndef _RENDER_H_
#define _RENDER_H_

#include <stdint.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//vector class for convenient math with 3D cartesian coordinates
class Vector {
    public:
    float x, y, z;
    Vector(float x0, float y0, float z0);
    float dot( Vector v);
    float magnitude();
    Vector cross( Vector v);
    Vector sum(Vector v);
    Vector diff(Vector v);
    void normalize();
    void scale(float k);
    float angle(Vector v);
};

//=====[Declarations (prototypes) of public functions]=========================

void render();
void transmit();
float getDistance(int t_s, int z_s);

//=====[#include guards - end]=================================================
 
#endif // _RENDER_H_
