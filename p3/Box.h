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
#include "Texture.h"

class Box: public Object3D
{
public:
    Box();
    Box( Texture* t );
    virtual ~Box();
    virtual void redraw();
    void textureRedraw();

protected:
    float length;
    Texture* texture;
};

#endif /*BOX_H_*/
