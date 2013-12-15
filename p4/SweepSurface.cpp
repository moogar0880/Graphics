/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SweepSurface.cpp - A class implementation representing a 3D sweep 
 *		surface object for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "SweepSurface.h"
#include "Triangle.h"
extern bool vaoSupported;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg SweepSurface Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SweepSurface::SweepSurface(){
    length = 1;
    texture = NULL;
    material = NULL;
    steps = 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Constructor for specifying the number of steps to use to complete 
 * 	the construction of the object and the vector of 2D points
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SweepSurface::SweepSurface(int s, std::vector<Point3*> v){
    length = 1;
    texture = NULL;
    material = NULL;
    steps = s;
    curve = v;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture enabled SweepSurface Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SweepSurface::SweepSurface(Texture* t){
    length = 1;
    texture = t;
    material = NULL;
    steps = 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture enabled SweepSurface Constructor with number of steps and
 *	vector of 2D points set
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SweepSurface::SweepSurface(int s, Texture* t, std::vector<Point3*> v){
    length = 1;
    texture = t;
    material = NULL;
    steps = 0;
    curve = v;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SweepSurface Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SweepSurface::~SweepSurface(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SweepSurface redraw
 *    Handles actually drawing the SweepSurface object with the OpenGL
 *    framework.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void SweepSurface::redraw(){
	glPushMatrix();
	glBegin( GL_TRIANGLE_STRIP );
	if( texture != NULL ){
		float x2yAspect = texture->getWidth() / (float)texture->getHeight();
	    float yscale = 1.75f;
	    float xscale = yscale * x2yAspect;
		texture->enable();
    	for( int i = 0; i < steps; i++){
    		for(std::vector<Point3*>::iterator it = curve.begin(); it != curve.end(); ++it){
	    		glTexCoord2f(0.0, 0.0); glVertex2f((*it)->x + i, (*it)->y);
	    		glTexCoord2f(0.5, 1.0); glVertex2f((*it)->x + i, (*it)->y);
	    		glTexCoord2f(1.0, 0.0); glVertex2f((*it)->x + i, (*it)->y);
	    	}
    	}
    	glTranslatef( xLoc, yLoc, zLoc );
	    glRotatef( angle, dxRot, dyRot, dzRot );
	    glScalef( xscale * xSize, yscale * ySize, 1.0 );
		texture->disable();
	}
	else{
    	for( int i = 0; i < steps; i++){
    		for(std::vector<Point3*>::iterator it = curve.begin(); it != curve.end(); ++it){
	    		glVertex2f((*it)->x + i, (*it)->y);
	    	}
    	}
    	glTranslatef( xLoc, yLoc, zLoc );
        glRotatef( angle, dxRot, dyRot, dzRot );
        glScalef( xSize, ySize, zSize );
	}
	glEnd();
    glPopMatrix();
    glutSwapBuffers();
}
