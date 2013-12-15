/**
 * Box.h - a class implementation representing a Box object
 *           in OpenGL
 *
 * implemented by Can Xiong as a Cube class
 * Sep 26, 2012
 */

#ifndef BOX_H_
#define BOX_H_

#include <iostream>
#include "Object3D.h"

class Box: public Object3D
{
public:
    Box();
    virtual ~Box();
    virtual void redraw();

protected:

    float length;
};

#endif /*BOX_H_*/
