/**
 * Shape.h - an abstract class representing an OpenGL graphical object
 *
 * rdb
 * August 17, 2012
 * ----------------------------------------------
 * 09/05/12 - added getX and getY methods
 */
#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glut.h>
#include "Point.h"
class Shape
{
public:
   Shape();
   virtual ~Shape();

   void  setLocation( float x, float y ); // set the location/origin of object

   void  setSize( float xs, float ys );   // set the size of the object
   float getX();                          // return x location
   float getY();                          // return y location

   void setColor( float r, float g, float b ); // set color
   void setBorderColor( float r, float g, float b ); // set border color

   virtual void redraw() = 0;

protected:
   float xLoc, yLoc;         // location (origin) of the object
   float xSize, ySize;       // size of the object
   float red, green, blue;   // fill color
   float redB, greenB, blueB;// border colors
};

#endif /*SHAPE_H_*/

