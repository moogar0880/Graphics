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
    
    virtual void setLocation( float x, float y );
    virtual void redraw();
    virtual void bind();
    
protected:
    int   nPoints;
    //float dx[ 3 ];   // points of triangle relative to triangle location
    //float dy[ 3 ];
    
    point2 relPoints[ 3 ];
    vec3   vColors[ 3 ]; // colors of each vertex
    
    void   makeBuffers();
    void   buildShaders();
    void   sendXformToShader();
};

#endif /*TRIANGLE_H_*/
