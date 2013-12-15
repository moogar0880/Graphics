/**
 * SweepSurface.h - a class implementation representing a SweepSurface object
 *           in OpenGL
 *
 * implemented by Can Xiong as a Cube class
 * Sep 26, 2012
 */

#ifndef SWEEPSURFACE_H_
#define SWEEPSURFACE_H_

#include <iostream>
#include "Object3D.h"
#include "Texture.h"

class SweepSurface: public Object3D
{
public:
    SweepSurface();
    SweepSurface(int s, std::vector<Point3*> v);
    SweepSurface(Texture* t);
    SweepSurface(int s, Texture* t, std::vector<Point3*> v);
    virtual ~SweepSurface();
    virtual void redraw();

protected:
    float length;
    Texture* texture;
    int steps;
    std::vector<Point3*> curve;
};

#endif /*SWEEPSURFACE_H_*/