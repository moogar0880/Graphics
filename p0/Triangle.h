/**
 * Triangle.h - a class implementation representing a triangle object
 *           in OpenGL
 *
 * rdb
 * August 26, 2012
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_


#include "Shape.h"

class Triangle: public Shape
{
public:
   Triangle();
   virtual ~Triangle();

   virtual void redraw();

protected:
    int   nPoints;
    Point* points[ 3 ];
};

#endif /*TRIANGLE_H_*/
