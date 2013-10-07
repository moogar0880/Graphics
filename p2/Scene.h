/**
 * Scene.h - a class represent a scene: its objects and its view
 * 
 * 09/24/2013 rdb
 *            Some code taken from Can Xiong 770 assignment Fall 2012
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>
#include "Object3D.h"

class Scene 
{
public:
    Scene();

    void addObject( Object3D* object );
    void clear();

    void resetView();
    
    void setLookat( float eyeX, float eyeY, float eyeZ,
                    float lookX, float lookY, float lookZ,
                    float upX, float upY, float upZ );
    void setPerspective( float angle, float ratio, float near, float far );

    void setDrawAxes( int yesno );
    void drawCoordinateAxes( void );
    void redraw( void );

protected:
    //---- objects collection -------
    std::vector<Object3D*> objects;

    //----gluLookat parameters -------
    float eyeX, eyeY, eyeZ; // gluLookat eye position
    float lookX, lookY, lookZ; // gluLookat look position
    float upX, upY, upZ; // up vector

    //----gluPerspective parameters ----
    float viewAngle, aspectRatio, near, far; 


    //---- draw Axes flag ------------------------
    bool  drawAxes;
};

#endif /*SCENE_H_*/
