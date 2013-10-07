/**
 * Sphere.h - a class implementation representing a Sphere object
 *           in OpenGL
 * 
 * Can Xiong
 * Sep 26, 2012
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Object3D.h"

class Sphere: public Object3D
{
public:
   Sphere();
   virtual ~Sphere();
   
   virtual void redraw();
   
protected:
	float radius;
};

#endif /*SPHERE_H_*/
