/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Snowman.cpp - A class implementation representing a 3D snowman object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Snowman.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Snowman Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Snowman::Snowman(){
    head = new Head();
    head->setColor( 0, new Color( 0.46, 0.65, 1.0 ) );
    head->setLocation( 0, 0, 0 );
    head->setSize( 0.75, 0.75, 0.75 );

    buildNose();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Snowman method for building the nose of the snowman
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::buildNose(){
	nose = new Cone();
    nose->setRotate( 90, 0, 0, 0 );
    nose->setLocation( head->getX(), head->getY(), head->getZ() + 1 );
    nose->setSize( 0.5, 0.5, 0.5 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Snowman setSize
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setSize( float xs, float ys, float zs ){
    head->setSize( xs, ys, zs );
    float constant = 0.6666666667;
    nose->setSize( xs * constant, ys * constant, zs * constant );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Snowman setLocation
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setLocation( float x, float y, float z ){
    head->setLocation( x, y, z );
    nose->setLocation( head->getX(), head->getY(), head->getZ() + 0.9 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setRotate
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setRotate( float angle, float dx, float dy, float dz ){
    head->setRotate( angle, dx, dy, dz );
    nose->setRotate( angle, dx, dy, dz );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor int float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setColor( int index, float r, float g, float b ){
    if( index == 0 )
        head->setColor( r, g, b );
    else
        nose->setColor( r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setColor( float r, float g, float b ){
    setColor( 1, r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor int
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setColor( int index, Color* c ){
    if( index == 0 )
        head->setColor( c );
    else
        nose->setColor( c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::setColor( Color* c ){
    setColor( 1, c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Snowman Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Snowman::~Snowman(){
    delete head;
    delete nose;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Snowman redraw
 *    Handles actually drawing the Snowman object with the OpenGL
 *    framework.
 *
 *    The Snowman is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Snowman::redraw(){
    head->redraw();
    nose->redraw();
}
