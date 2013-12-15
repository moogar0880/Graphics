/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Donut.cpp - A class implementation representing a 3D donut object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Donut.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Donut Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Donut::Donut(){
    length = 1;
    texture = NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture endabled Donut Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Donut::Donut( Texture* t ){
    length = 1;
    texture = t;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Donut Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Donut::~Donut(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Donut redraw
 *    Handles actually drawing the Donut object with the OpenGL
 *    framework.
 *
 *    The Donut is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Donut::redraw(){
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
	        glutSolidTorus( xSize/4, xSize/2, 10, 50 );
	    glPopMatrix();
	}
}

void Donut::textureRedraw(){
	float x2yAspect = texture->getWidth() / (float)texture->getHeight();
	glMatrixMode( GL_MODELVIEW );

	texture->enable();
	// glBegin( GL_QUADS );
	glTranslatef( xLoc, yLoc, zLoc );
    glRotatef( angle, dxRot, dyRot, dzRot );
    // glScalef( xSize, ySize, zSize );
    float yscale = ySize * x2yAspect;
    float xscale = yscale * x2yAspect;
    glScalef( xscale * xSize, yscale * ySize, 1.0 );
    glutSolidTorus( xscale * xSize, yscale * ySize, 10, 50 );
    // glEnd();
	texture->disable();
	glutSwapBuffers();
}
