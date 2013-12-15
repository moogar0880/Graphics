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
#include "Texture.h"

class Sphere: public Object3D
{
public:
   Sphere();
   Sphere( Texture* t );
   virtual ~Sphere();
   void textureRedraw();
   
   virtual void redraw();
   
protected:
	float radius;
	Texture* texture;
};

#endif /*SPHERE_H_*/
