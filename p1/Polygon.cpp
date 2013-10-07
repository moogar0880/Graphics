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
 * No Arg Polygon Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Polygon::Polygon(){
   points[0] = new Point(0.0,  0.0);
   points[1] = new Point(100.0,0.0);
   points[2] = new Point(100.0,200.0);
   points[3] = new Point(0.0,  200.0);

   nPoints = 4;
}

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
void Polygon::redraw(){
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
