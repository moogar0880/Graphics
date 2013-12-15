/**
 * Eye.h - a class implementation representing an Eye object
 *           in OpenGL
 */

#ifndef EYE_H_
#define EYE_H_

#include <iostream>
#include "Object3D.h"
#include "Donut.h"
#include "Sphere.h"

class Eye: public Object3D
{
public:
    Eye();
    virtual ~Eye();
    void setSize( float xs, float ys, float zs );
    void setColor( int index, float r, float g, float b );   // set color
    void setColor( float r, float g, float b );   // set color 0
    void setColor( int index, Color* c );
    void setColor( Color* c );   // set color 0
    void setLocation( float x, float y, float z ); // set location
    void setRotate( float angle, float dx, float dy, float dz ); // set rotate
    virtual void redraw();

protected:
	// Vector of all composite objects
	// std::vector<Object3D*> composites;
	void buildEye( void );
	void buildPupil( void );
	Donut* sclera;
	Sphere* pupil;
};

#endif /*EYE_H_*/
