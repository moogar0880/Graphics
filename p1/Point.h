/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Point.h - A class implementation representing a point object
 *    for OpenGL coordinate systems
 *
 * Jonathan Nappi
 * September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef POINT_H_
#define POINT_H_

class Point
{
public:
	Point();
	Point(float x, float y);
	~Point();

	float getX();
	float getY();

	void print();
protected:
	float x;
	float y;
};

#endif /*POINT_H_*/
