/**
 * Donut.h - a class implementation representing a Donut object
 *           in OpenGL
 */

#ifndef DONUT_H_
#define DONUT_H_

#include <iostream>
#include "Object3D.h"

class Donut: public Object3D
{
public:
    Donut();
    virtual ~Donut();
    virtual void redraw();

protected:
    float length;
};

#endif /*DONUT_H_*/
