/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hat.cpp - A class implementation representing a 3D hat object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Hat.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Hat Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Hat::Hat(){
    buildHat();
    buildTip();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hat method for building the body of the hat
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::buildHat(){
	cone = new Cone();
    cone->setColor( new Color( 1, 1, 0 ) );
    cone->setLocation( 0, 0, 0 );
    cone->setSize( 1, 1, 1 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hat method for building the tip of the hat
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::buildTip(){
	tip = new Sphere();
	tip->setColor( new Color( 0, 0, 1 ) );
    tip->setLocation( 0, 1.1, 0 );
    tip->setSize( 0.15, 0.15, 0.15 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setSize
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setSize( float xs, float ys, float zs ){
    cone->setSize( xs, ys, zs );
    tip->setSize( xs * 0.15, ys * 0.15, zs * 0.15 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setLocation
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setLocation( float x, float y, float z ){
    cone->setLocation( x, y, z );
    tip->setLocation( cone->getX(), cone->getY() + 0.5, cone->getZ() );
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setRotate
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setRotate( float angle, float dx, float dy, float dz ){
    cone->setRotate( angle, dx, dy, dz );
    tip->setRotate( angle, dx, dy, dz );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setColor int float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setColor( int index, float r, float g, float b ){
    if( index == 0 )
        cone->setColor( r, g, b );
    else
        tip->setColor( r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setColor float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setColor( float r, float g, float b ){
    setColor( 1, r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setColor int
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setColor( int index, Color* c ){
    if( index == 0 )
        cone->setColor( c );
    else
        tip->setColor( c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Hat setColor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::setColor( Color* c ){
    setColor( 1, c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hat Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Hat::~Hat(){
    delete cone;
    delete tip;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hat redraw
 *    Handles actually drawing the Hat object with the OpenGL
 *    framework.
 *
 *    The Hat is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Hat::redraw(){
    cone->redraw();
    tip->redraw();
}
