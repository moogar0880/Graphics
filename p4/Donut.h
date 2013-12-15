/**
 * Donut.h - a class implementation representing a Donut object
 *           in OpenGL
 */

#ifndef DONUT_H_
#define DONUT_H_

#include <iostream>
#include "Object3D.h"
#include "Texture.h"

class Donut: public Object3D
{
public:
    Donut();
    Donut( Texture* t );
    virtual ~Donut();
    virtual void redraw();
    void textureRedraw();

protected:
    float length;
    Texture* texture;
};

#endif /*DONUT_H_*/
