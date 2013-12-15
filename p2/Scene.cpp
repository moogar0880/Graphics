/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Scene.cpp - a class represent a scene: its objects and its view
 *
 * 09/24/2013 rdb
 *            Some code taken from Can Xiong 770 assignment Fall 2012
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "ControlPanel.h"
#include "Scene.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialize any values, register callbacks
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Scene::Scene(){
    resetView();
    drawAxes = true;
    parallel = false;
    left = right = bottom = top = onear = ofar = fleft = fright = fbottom =
           ftop = fnear = ffar = 0.0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the parallel projection status to b
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setParallelStatus( bool b ){
    parallel = b;
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return parallel projection status
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool Scene::getParallelStatus( ){
    return parallel;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Restore the view to default settings
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::resetView(){
    setLookat( 10, 3, 10, // eye
               0, 0, 0,   // at
               0, 1, 0 ); // up

    setPerspective( 10, 1.33, 0.1, 100.0 ); //should calc windowWid / windowHt
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add a new object to the scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::addObject( Object3D *newObject ){
    objects.push_back( newObject );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Clear the scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::clear(){
    objects.clear();
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the scene's lookat parameters
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setLookat( float eyeX, float eyeY, float eyeZ,
                    float lookX, float lookY, float lookZ,
                    float upX, float upY, float upZ )
{
    this->eyeX = eyeX;
    this->eyeY = eyeY;
    this->eyeZ = eyeZ;
    this->lookX = lookX;
    this->lookY = lookY;
    this->lookZ = lookZ;
    this->upX = upX;
    this->upY = upY;
    this->upZ = upZ;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return the current scene's lookat parameters as a float array
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float* Scene::getLookat(){
    float* toRet = new float[9];
    toRet[0] = this->eyeX;
    toRet[1] = this->eyeY;
    toRet[2] = this->eyeZ;
    toRet[3] = this->lookX;
    toRet[4] = this->lookY;
    toRet[5] = this->lookZ;
    toRet[6] = this->upX;
    toRet[7] = this->upY;
    toRet[8] = this->upZ;
    return toRet;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the current scene's perspective
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setPerspective ( float angle, float ratio, float near, float far ){
    this->viewAngle = angle;
    this->aspectRatio = ratio;
    this->near = near;
    this->far = far;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return the current scene's perspective as a float array
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float* Scene::getPerspective(){
    float* toRet = new float[4];
    toRet[0] = this->viewAngle;
    toRet[1] = this->aspectRatio;
    toRet[2] = this->near;
    toRet[3] = this->far;
    return toRet;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the current scene's ortho parameters
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setOrtho( float* vals ){
    left   = vals[0];
    right  = vals[1];
    bottom = vals[2];
    top    = vals[3];
    onear  = vals[4];
    ofar   = vals[5];
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the current scene's frustum parameters
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setFrustum( float* vals ){
    fleft   = vals[0];
    fright  = vals[1];
    fbottom = vals[2];
    ftop    = vals[3];
    fnear  = vals[4];
    ffar   = vals[5];
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Draw the world coord axes to help orient the viewer
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::drawCoordinateAxes(){
    float scale = 1.8f;  // convenient scale factor for experimenting with size
    glPushMatrix();

        glScalef( scale, scale, scale );
        float origin[ 3 ] = { 0, 0, 0 };

        float xaxis[ 3 ] = { 1, 0, 0 },
              yaxis[ 3 ] = { 0, 1, 0 },
              zaxis[ 3 ] = { 0, 0, 1 };

        glLineWidth( 3.0 );

        glBegin( GL_LINES );
            glColor3f( 1, 0, 0 ); // X axis is red.
            glVertex3fv( origin );
            glVertex3fv( xaxis );
            glColor3f( 0, 1, 0 ); // Y axis is green.
            glVertex3fv( origin );
            glVertex3fv( yaxis );
            glColor3f( 0, 0, 1 ); // z axis is blue.
            glVertex3fv( origin );
            glVertex3fv( zaxis );
        glEnd();
    glPopMatrix();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Scene's redraw method
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::redraw( void ){
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();                // Reset The Projection Matrix

    // Only do perspective for now
    gluPerspective( viewAngle, aspectRatio, near, far );

    if( parallel )
        glOrtho( left, right, bottom, top, onear, ofar );
    else
        glFrustum( fleft, fright, fbottom, ftop, fnear, ffar );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();                // Reset The Projection Matrix

    gluLookAt( eyeX, eyeY, eyeZ,
              lookX, lookY, lookZ,
              upX, upY, upZ );

    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    if( drawAxes )
        drawCoordinateAxes();

    // create a vector iterator to access and draw the objects
    std::vector<Object3D*>::iterator it;
    for ( it = objects.begin(); it != objects.end(); it++ )
          ( *it )->redraw();
    glFlush();                         // send all output to display
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Determine if the current scene will draw the coordinate axes.
 *  0 = false, non-zero = true
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setDrawAxes( int yesno ){
    drawAxes = yesno;
}
