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
    Scene(  );
    Scene( char* descrip );

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
    float* getLookat( void );
    float* getPerspective( void );
    void setParallelStatus( bool b );
    bool getParallelStatus( );
    void setOrtho( float* vals );
    void setFrustum( float* vals );
    char* getDescription();
    void setAmbientLoc( int x, int y, int z );
    void setDirectionalLoc( int x, int y, int z );
    void setLightColor( int f, float r, float g, float b );

protected:
    //---- objects collection -------
    std::vector<Object3D*> objects;

    //----gluLookat parameters -------
    float eyeX, eyeY, eyeZ; // gluLookat eye position
    float lookX, lookY, lookZ; // gluLookat look position
    float upX, upY, upZ; // up vector

    //----gluPerspective parameters ----
    float viewAngle, aspectRatio, near, far;

    //----glOrtho----
    float left, right, bottom, top, onear, ofar;

    //----glfrustum----
    float fleft, fright, fbottom, ftop, fnear, ffar;

    //---- draw Axes flag ------------------------
    bool  drawAxes, parallel;

    //---- ambient light position ----------------
    float alx, aly, alz, alw;

    //---- directional light position ------------
    float dlx, dly, dlz, dlw;

    //---- ambient light color -------------------
    float alr, alg, alb, ala;

    //---- directional light color --------------- 
    float dlr, dlg, dlb, dla;
    
    char* description;
};

#endif /*SCENE_H_*/
