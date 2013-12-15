/**
 * Head.h - a class implementation representing an Head object
 *           in OpenGL
 */

#ifndef HEAD_H_
#define HEAD_H_

#include <iostream>
#include "Object3D.h"
#include "Sphere.h"
#include "Eye.h"

class Head: public Object3D
{
public:
    Head();
    virtual ~Head();
    void setSize( float xs, float ys, float zs );
    void setLocation( float x, float y, float z ); // set location override
    void setRotate( float angle, float dx, float dy, float dz ); // set rotate
    void setColor( int index, float r, float g, float b );   // set color
    void setColor( float r, float g, float b );   // set color 0
    void setColor( int index, Color* c );
    void setColor( Color* c );   // set color 0
    virtual void redraw();

protected:
	void buildEyes( void );
    Sphere* head;
    Eye *left, *right;
};

#endif /*HEAD_H_*/
