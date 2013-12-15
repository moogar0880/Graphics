/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Head.cpp - A class implementation representing a 3D head object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Head.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Head Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Head::Head(){
    head = new Sphere();
    head->setColor( new Color( 0.46, 0.65, 1.0 ) );
    head->setLocation( 0, 0, 0 );
    head->setSize( 0.75, 0.75, 0.75 );

    buildEyes();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Head method for building the eyes of the head
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::buildEyes(){
    left = new Eye();
    left->setColor( new Color( 0, 0, 1 ) );
    left->setLocation( head->getX() + 1, head->getY() + 0.5, head->getZ() + 1 );
    left->setSize( 0.5, 0.5, 0.5 );

    right = new Eye();
    right->setColor( new Color( 0, 0, 1 ) );
    right->setLocation( head->getX() + 0.5, head->getY() + 0.5, head->getZ() + 1.5 );
    right->setSize( 0.5, 0.5, 0.5 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setSize
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setSize( float xs, float ys, float zs ){
    head->setSize( xs, ys, zs );
    float constant = 0.6666666667;
    left->setSize( xs * constant, ys * constant, zs * constant );
    right->setSize( xs * constant, ys * constant, zs * constant );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setLocation
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setLocation( float x, float y, float z ){
    head->setLocation( x, y, z );
    left->setLocation( head->getX() + 0.5, head->getY() + 0.5, head->getZ() + 1.5 );
    right->setLocation( head->getX() + 1, head->getY() + 0.5, head->getZ() + 1);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setRotate
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setRotate( float angle, float dx, float dy, float dz ){
    head->setRotate( angle, dx, dy, dz );
    left->setRotate( angle, dx, dy, dz );
    right->setRotate( angle, dx, dy, dz );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor int float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setColor( int index, float r, float g, float b ){
    if( index == 0 )
        head->setColor( r, g, b );
    else{
        left->setColor( r, g, b );
        right->setColor( r, g, b );
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor float float float
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setColor( float r, float g, float b ){
    setColor( 1, r, g, b );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor int
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setColor( int index, Color* c ){
    if( index == 0 )
        head->setColor( c );
    else{
        left->setColor( c );
        right->setColor( c  );
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * OVERRIDE Head setColor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::setColor( Color* c ){
    setColor( 1, c );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Head Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Head::~Head(){
    delete head;
    delete left;
    delete right;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Head redraw
 *    Handles actually drawing the Head object with the OpenGL
 *    framework.
 *
 *    The Head is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Head::redraw(){
    head->redraw();
    left->redraw();
    right->redraw();
}
