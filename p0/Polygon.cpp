/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Polygon.cpp - A class implementation representing a polygon object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Polygon.h"
#include <iostream>
#include <stdarg.h>
#include <vector>
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Polygon Constructor accepts width and height double arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Polygon::Polygon(int size, ...)
{
   std::vector<Point*> pointsList;
   va_list ap;
   va_start(ap,size);
   for( int i = 0; i < size; i++){
      float xVal, yVal;
      xVal = (float)va_arg(ap,double);
      yVal = (float)va_arg(ap,double);
      pointsList.push_back(new Point(xVal,yVal));
   }
   va_end(ap);
   std::vector<Point*>::iterator it;
   nPoints = size;
   int i = 0;
   for(it = pointsList.begin(); it < pointsList.end(); it++){
      points[ i++ ] = (*it);
   }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectanlge Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Polygon::~Polygon(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Polygon redraw
 *    Handles actually drawing the Polygon object with the OpenGL
 *    framework.
 *
 *    The polygon is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Polygon::redraw()
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
