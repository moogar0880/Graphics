/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectangle.cpp - A class implementation representing a rectangle object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Rectangle.h"
#include <iostream>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Rectangle Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Rectangle::Rectangle(){
   points[0] = new Point(0.0,  0.0);
   points[1] = new Point(100.0,0.0);
   points[2] = new Point(100.0,200.0);
   points[3] = new Point(0.0,  200.0);

   nPoints = 4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectangle Constructor accepts width and height float arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Rectangle::Rectangle(float w, float h)
{
   points[0] = new Point(0.0,0.0);
   points[1] = new Point(w,0.0);
   points[2] = new Point(w,h);
   points[3] = new Point(0.0,h);

   nPoints = 4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectanlge Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Rectangle::~Rectangle(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectangle redraw
 *    Handles actually drawing the Rectangle object with the OpenGL
 *    framework.
 *
 *    The rectangle is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Rectangle::redraw(){
   if( drawBorder ){
      glColor3f( redB, greenB, blueB );
      glBegin( GL_LINE_LOOP );

      for ( int i = 0; i < nPoints; i++ ){
         glVertex2f( xLoc + points[ i ]->getX() * xSize,
                     yLoc + points[ i ]->getY() * ySize );
      }
      glEnd();
   }
   if( drawFill ){
      glColor3f( red, green, blue );
      glBegin( GL_POLYGON );

      for ( int i = 0; i < nPoints; i++ ){
         glVertex2f( xLoc + points[ i ]->getX() * xSize,
                     yLoc + points[ i ]->getY() * ySize );
      }
      glEnd();
   }
}
