/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Clown.cpp - A class implementation representing a 3D clown object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Clown.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Clown Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Clown::Clown(){
    head = new Head();
    head->setColor( 0, new Color( 0.46, 0.65, 1.0 ) );
    head->setLocation( 0, 0, 0 );
    head->setSize( 0.75, 0.75, 0.75 );

    buildHat();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Clown method for building the hat of the clown
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::buildHat(){
	hat = new Hat();
    hat->setLocation( head->getX(), head->getY() + 0.75, head->getZ() );
    hat->setSize( 0.5, 0.5, 0.5 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setSize
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setSize( float xs, float ys, float zs ){
    head->setSize( xs, ys, zs );
    float constant = 0.6666666667;
    hat->setSize( xs * constant, ys * constant, zs * constant );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setLocation
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setLocation( float x, float y, float z ){
    head->setLocation( x, y, z );
    hat->setLocation( head->getX(), head->getY() + 0.75, head->getZ() );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setRotate
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setRotate( float angle, float dx, float dy, float dz ){
    head->setRotate( angle, dx, dy, dz );
    hat->setRotate( angle, dx, dy, dz );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setColor int float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setColor( int index, float r, float g, float b ){
    if( index == 0 )
        head->setColor( r, g, b );
    else
        hat->setColor( r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setColor float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setColor( float r, float g, float b ){
    setColor( 1, r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setColor int
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setColor( int index, Color* c ){
    if( index == 0 )
        hat->setColor( c );
    else
        head->setColor( c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Clown setColor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::setColor( Color* c ){
    setColor( 0, c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Clown Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Clown::~Clown(){
    delete head;
    delete hat;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Clown redraw
 *    Handles actually drawing the Clown object with the OpenGL
 *    framework.
 *
 *    The Clown is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Clown::redraw(){
    head->redraw();
    hat->redraw();
}
