/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Polygon.h - A class implementation representing a polygon object
 *    for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef POLYGON_H_
#define POLYGON_H_

#include "Shape.h"

class Polygon: public Shape
{
public:
   Polygon();
   Polygon(int size, ...);
   virtual ~Polygon();

   virtual void redraw();

protected:
   int   nPoints;
   Point* points[ 90 ];// points of polygon relative to polygon location
};

#endif /*POLYGON_H_*/
