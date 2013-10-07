/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D.cpp - An abstract class representing a 3D OpenGL graphical
 *   object implementation representing a polygon object
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Object3D.h"
#include <iostream>
#include "Color.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Object3D Constructor creates a new object at (0,0,0) of size
 *  (1,1,1) with a default color of Red (1,0,0)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Object3D::Object3D(){
    Color* color = new Color( 1.0, 0.0, 0.0 );
    colors.push_back(color);
    setLocation( 0, 0, 0 );
    setSize( 1, 1, 1 );
    setRotate( 0, 0, 0, 0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Object3D::~Object3D(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D SetLocation
 *      Set the location of the object to the (x,y,z) position defined by
 *      the provided arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setLocation( float x, float y, float z ){
    xLoc = x;
    yLoc = y;
    zLoc = z;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D getX returns the value of the x origin of the shape
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float Object3D::getX(){
    return xLoc;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D getY returns the value of the y origin of the shape
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float Object3D::getY(){
    return yLoc;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D getZ returns the value of the z origin of the shape
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float Object3D::getZ(){
    return zLoc;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D getLocation returns the value of the location as a Point3
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Point3* Object3D::getLocation(){
    return new Point3( xLoc, yLoc, zLoc );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setColor
 *  set the "nominal" color of the object to the specified color; this
 *   does not require that ALL components of the object must be the same
 *   color. Typically, the largest component will take on this color,
 *   but the decision is made by the child class.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setColor( Color* c ){
    setColor( 0, c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setColor sets the nominal color (index 0) to the specified
 *   color with floats
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setColor( float r, float g, float b ){
    setColor( 0, new Color( r, g, b ));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setColor sets the index color entry to the specified color
 *  with floats
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setColor( int i, float r, float g, float b ){
    setColor( i, new Color( r, g, b ));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setColor sets the i-th color entry to the specidied color
 *  with Color c
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setColor( int i, Color* c ){
    if ( i < 0 || i > MAX_COLORS ){ // should throw an exception!
        std::cerr << "*** ERROR *** Object3D.setColor: bad index: " << i << "\n";
        return;
    }
    Color* newColor = new Color( *c );
    if ( i >= colors.size() ){  // need to add entries to vector
        for ( int n = (int)colors.size(); n < i; n++ ) // fill w/ black if needed
            colors.push_back( new Color() );
        colors.push_back( newColor );  // put desired color at desired index
    }
    else{ // now delete old entry and update the index
        delete colors[ i ];
        colors[ i ] = newColor;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setSize
 *    set the size of the shape to be scaled by xs, ys, zs
 *      That is, the shape has an internal fixed size, the shape parameters
 *      scale that internal size.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setSize( float xs, float ys, float zs ){
    xSize = xs;
    ySize = ys;
    zSize = zs;
}

/**
 * set the rotation parameters: angle, and axis specification
 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Object3D setRotate sets the rotation parameters: angle, and axis
 *      specification
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Object3D::setRotate( float a, float dx, float dy, float dz ){
    angle = a;
    dxRot = dx;
    dyRot = dy;
    dzRot = dz;
}
