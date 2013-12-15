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
    description = (char*)"Default Scene Description";
    //Set lighting intensity and color
    GLfloat ambientLight[] = {1, 1, 0.4, 0.5};
    GLfloat bluish[] = { 0.3f, 0.3f, 0.7f, 1 };
    GLfloat grenish[] = { 0.1f, 0.7f, 0.1f, 1 };
    GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
    GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
    GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

    //Set the light position
    // GLfloat lightPosition[] = {-1, 1, 1, 0};
    alx = dlx -1;
    aly = alz = dly = dlz = 1; 
    alw = dlw = 0;
    GLfloat lightPosition[] = {alx, aly, alz, alw} ;
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );

    glEnable( GL_LIGHT1 );

    //Set lighting intensity and color
    // GLfloat lightPosition2[] = {-1, 1, 1, 0};
    GLfloat lightPosition2[] = {dlx, dly, dlz, dlw};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, grenish);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightPosition2);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialize any values, register callbacks
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Scene::Scene( char* descrip ){
    resetView();
    drawAxes = true;
    parallel = false;
    left = right = bottom = top = onear = ofar = fleft = fright = fbottom =
           ftop = fnear = ffar = 0.0;
    description = descrip;
    std::cerr << description << std::endl;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return the description for the scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
char* Scene::getDescription( ){
    return description;
    std::cerr << description << std::endl;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the ambient light source location
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setAmbientLoc( int x, int y, int z ){
    alx = x;
    aly = y;
    alz = z;
    GLfloat lightPosition[] = {alx, aly, alz, alw} ;
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the directional light source location
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setDirectionalLoc( int x, int y, int z ){
    dlx = x;
    dly = y;
    dlz = z;
    GLfloat lightPosition2[] = {dlx, dly, dlz, dlw};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the perspective sliders
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::setLightColor( int f, float r, float g, float b ){
    GLfloat lightC[] = {r, g, b};
    if( !f ){
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightC);
    }
    else{
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightC);
    }
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
    // setLookat( 10, 3, 10, // eye
    //            0, 0, 0,   // at
    //            0, 1, 0 ); // up
    setLookat(20,6,20,0,0,0,0,2,0);
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
