/**
 * Snowman.h - a class implementation representing an Snowman object
 *           in OpenGL
 */

#ifndef SNOWMAN_H_
#define SNOWMAN_H_

#include <iostream>
#include "Object3D.h"
#include "Head.h"
#include "Cone.h"

class Snowman: public Object3D
{
public:
    Snowman();
    virtual ~Snowman();
    void setSize( float xs, float ys, float zs );
    void setLocation( float x, float y, float z ); // set location override
    void setRotate( float angle, float dx, float dy, float dz ); // set rotate
    void setColor( int index, float r, float g, float b );   // set color
    void setColor( float r, float g, float b );   // set color 0
    void setColor( int index, Color* c );
    void setColor( Color* c );   // set color 0
    virtual void redraw();

protected:
    void buildNose( void );
    Head* head;
    Cone* nose;
};

#endif /*SNOWMAN_H_*/
