/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sphere.cpp - A class implementation representing a 3D sphere object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Sphere.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Sphere Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Sphere::Sphere(){
    radius = 1;
    texture = NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture endabled Sphere Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Sphere::Sphere( Texture* t ){
    radius = 1;
    texture = t;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sphere Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Sphere::~Sphere(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sphere redraw
 *    Handles actually drawing the Sphere object with the OpenGL
 *    framework.
 *
 *    The Sphere is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Sphere::redraw(){
	if( texture != NULL )
		textureRedraw();
	else{
	    glPushMatrix();
	        glColor3f( colors[0]->r, colors[0]->g, colors[0]->b );
	        glTranslatef( xLoc, yLoc, zLoc );
	        glRotatef( angle, dxRot, dyRot, dzRot );
	        glScalef( xSize, ySize, zSize );
	        material->activate();
            glColorMaterial( GL_FRONT_AND_BACK, GL_SPECULAR );
	        glutSolidSphere( radius, 360, 360 );
	    glPopMatrix();
	    glutSwapBuffers();
	}
}

void Sphere::textureRedraw(){
	float x2yAspect = texture->getWidth() / (float)texture->getHeight();
    float yscale = ySize * x2yAspect;
    float xscale = xSize * x2yAspect;
	glMatrixMode( GL_MODELVIEW );

	texture->enable();
	glTranslatef( xLoc, yLoc, zLoc );
    glRotatef( angle, dxRot, dyRot, dzRot );
	glTranslatef( 0.0, 0.0, 0.0 );
    glScalef( xscale * xSize, yscale * ySize, 2.0 );
    glutSolidSphere( radius, 360, 360 );
	texture->disable();
	glutSwapBuffers();
}
