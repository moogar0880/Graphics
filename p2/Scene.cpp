/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * 09/24/2013 rdb
 *            Some code taken from Can Xiong 770 assignment Fall 2012
 */

#include "ControlPanel.h"
#include "Scene.h"

//#include <math.h>

//------------------ Constructors ------------------------------------
/** Initialize any values, register callbacks
 */
Scene::Scene()
{
    resetView();
    drawAxes = true;
}

//-------------- resetView -----------------------------------------
/**
 *  restore the view to default settings
 */
void Scene::resetView()
{
    setLookat( 10, 3, 10, // eye
               0, 0, 0,   // at
               0, 1, 0 ); // up

    setPerspective( 10, 1.33, 0.1, 100.0 ); //should calc windowWid / windowHt
}

//--------------------------------------------------------------------
void Scene::addObject( Object3D *newObject )
{
    objects.push_back( newObject );
}
//--------------------------------------------------------------------
void Scene::clear()
{
    objects.clear();
    redraw();
}

//---------------------------------------------------------------------
/**
 *  set lookat parameters
 */
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
//---------------------------------------------------------------------
/**
 *  set perspective parameters
 */
void Scene::setPerspective ( float angle, float ratio, float near, float far )
{
    this->viewAngle = angle;
    this->aspectRatio = ratio;
    this->near = near;
    this->far = far;
}

//---------------- drawing coordinate axes -----------------------
/**
 * Draw the world coord axes to help orient viewer.
 */
void Scene::drawCoordinateAxes()
{
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
//---------------------------------------------------------------------
void Scene::redraw( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();                // Reset The Projection Matrix

    // Only do perspective for now
    gluPerspective( viewAngle, aspectRatio, near, far );
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
//---------------- setDrawAxes( int )  -----------------------
/**
 *  0 means don't draw the axes
 * non-zero means draw them
 */
//-------------------------------------------
void Scene::setDrawAxes( int yesno )
{
    drawAxes = yesno;
}
