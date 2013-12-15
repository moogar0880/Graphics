/**
 * Cone.h - a class implementation representing a Cone object
 *           in OpenGL
 */

#ifndef CONE_H_
#define CONE_H_

#include <iostream>
#include "Object3D.h"
#include "Texture.h"

class Cone: public Object3D
{
public:
    Cone();
    Cone( Texture* t );
    virtual ~Cone();
    virtual void redraw();
    void textureRedraw();

protected:
    float length;
    Texture* texture;
};

#endif /*CONE_H_*/
