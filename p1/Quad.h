/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Quad.h - A class implementation representing an object with any 4
 *	points for OpenGL
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef QUAD_H_
#define QUAD_H_

#include "Shape.h"

class Quad: public Shape
{
public:
	Quad();
   Quad(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4);
   Quad(Point* p1, Point* p2, Point* p3, Point* p4);
   virtual ~Quad();

   virtual void redraw();

protected:
   int   nPoints;
   Point* points[ 4 ];// points of quad relative to quad location
};

#endif /*QUAD_H_*/
