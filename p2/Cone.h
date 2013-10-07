/**
 * Cone.h - a class implementation representing a Cone object
 *           in OpenGL
 */

#ifndef CONE_H_
#define CONE_H_

#include <iostream>
#include "Object3D.h"

class Cone: public Object3D
{
public:
    Cone();
    virtual ~Cone();
    virtual void redraw();

protected:
    float length;
};

#endif /*CONE_H_*/
