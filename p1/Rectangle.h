/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rectangle.h - A class implementation representing a rectangle object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

class Rectangle: public Shape
{
public:
   Rectangle();
   Rectangle(float w, float h);
   virtual ~Rectangle();

   virtual void redraw();

protected:
   int   nPoints;
   Point* points[ 4 ];// points of rectangle relative to rectangle location
};

#endif /*RECTANGLE_H_*/
