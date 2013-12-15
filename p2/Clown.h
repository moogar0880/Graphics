/**
 * Clown.h - a class implementation representing an Clown object
 *           in OpenGL
 */

#ifndef CLOWN_H_
#define CLOWN_H_

#include <iostream>
#include "Object3D.h"
#include "Head.h"
#include "Hat.h"

class Clown: public Object3D
{
public:
    Clown();
    virtual ~Clown();
    void setSize( float xs, float ys, float zs );
    void setLocation( float x, float y, float z ); // set location override
    void setRotate( float angle, float dx, float dy, float dz ); // set rotate
    virtual void redraw();
    void setColor( int index, float r, float g, float b );   // set color
    void setColor( float r, float g, float b );   // set color 0
    void setColor( int index, Color* c );
    void setColor( Color* c );   // set color 0

protected:
    void buildHat( void );
    Head* head;
    Hat* hat;
};

#endif /*CLOWN_H_*/
