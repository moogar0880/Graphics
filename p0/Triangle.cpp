/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Triangle.cpp - A class implementation representing a triangle object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "Triangle.h"
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Triangle Constructor accepts width and height float arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Triangle::Triangle()
{
   points[0] = new Point(0.0,  0.0);
   points[1] = new Point(40.0, 0.0);
   points[2] = new Point(20.0, 75.0);
   nPoints = 3;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Triangle Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Triangle::~Triangle(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Polygon redraw
 *    Handles actually drawing the triangle object with the OpenGL
 *    framework.
 *
 *    The triangle is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Triangle::redraw()
{
   glColor3f( redB, greenB, blueB );

   glBegin( GL_LINE_LOOP );

   for ( int i = 0; i < nPoints; i++ ){
      glVertex2f( xLoc + points[ i ]->getX() * xSize,
                  yLoc + points[ i ]->getY() * ySize );
   }
   glEnd();

   glColor3f( red, green, blue );
   glBegin( GL_POLYGON );

   for ( int i = 0; i < nPoints; i++ ){
      glVertex2f( xLoc + points[ i ]->getX() * xSize,
                  yLoc + points[ i ]->getY() * ySize );
   }
   glEnd();
}
