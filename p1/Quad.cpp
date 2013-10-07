/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quad.cpp - A class implementation representing a quad object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Quad.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Quad Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Quad::Quad(){
   points[0] = new Point(200.0,200.0);
   points[1] = new Point(100.0,200.0);
   points[3] = new Point(0.0,  400.0);
   points[2] = new Point(250.0,350.0);

   nPoints = 4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quad Constructor accepts 8 float arguments to use as point coordinates
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Quad::Quad(float x1, float y1, float x2, float y2, float x3, float y3,
           float x4, float y4)
{
   points[0] = new Point(x1,y1);
   points[1] = new Point(x2,y2);
   points[3] = new Point(x3,y3);
   points[2] = new Point(x4,y4);

   nPoints = 4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quad Constructor accepts 4 point arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Quad::Quad(Point* p1, Point* p2, Point* p3, Point* p4)
{
   points[0] = p1;
   points[1] = p2;
   points[2] = p3;
   points[3] = p4;

   nPoints = 4;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectanlge Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Quad::~Quad(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quad redraw
 *    Handles actually drawing the Quad object with the OpenGL
 *    framework.
 *
 *    The quad is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Quad::redraw(){
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
