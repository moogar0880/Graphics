/**
 * Hat.h - a class implementation representing an Hat object
 *           in OpenGL
 */

#ifndef HAT_H_
#define HAT_H_

#include <iostream>
#include "Object3D.h"
#include "Cone.h"
#include "Sphere.h"

class Hat: public Object3D
{
public:
    Hat();
    virtual ~Hat();
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
	void buildTip( void );
	Cone* cone;
	Sphere* tip;
};

#endif /*HAT_H_*/
