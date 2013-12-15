/**
 * Object3D.h - an abstract class representing an OpenGL graphical object
 *
 * rdb
 * 09/23/13
 *
 * Based on code created by Can Xiong, Fall 2012
 *
 */
#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include <vector>
#include "opengl.h"
#include "Color.h"
#include "Point3.h"
#include "Material.h"
#include "Triangle.h"

class Object3D
{
public:
    Object3D();
    virtual ~Object3D();

    void setLocation( float x, float y, float z ); // set location
    void setSize( float xs, float ys, float zs );   // set object size
    void setRotate( float angle, float dx, float dy, float dz ); // set rotate

    float getX();                          // return x location
    float getY();                          // return y location
    float getZ();                          // return z location
    Point3* getLocation();                 // return location as a Point

    void setColor( int index, float r, float g, float b );   // set color
    void setColor( float r, float g, float b );   // set color 0

    void setColor( int index, Color* c );
    void setColor( Color* c );   // set color 0
    void setMaterial( int m );
    void setMaterial( Material* m );

    std::vector<Triangle*> surface;

    virtual void redraw() = 0;

    static const int MAX_COLORS = 20;  // arbitrary number to keep an parameter
                                  //   error to setColor from closing down app

protected:
    float xLoc, yLoc, zLoc;        // location (origin) of the object
    float xSize, ySize, zSize;     // size of the object
    float angle, dxRot, dyRot, dzRot; // rotation angle and axis

    std::vector<Color*> colors;
    Material* material;
};

#endif /*OBJECT3D_H_*/

