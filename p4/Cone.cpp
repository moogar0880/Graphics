/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Cone.cpp - A class implementation representing a 3D cone object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Cone.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Cone Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Cone::Cone(){
    length = 1;
    texture = NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Textured Cone Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Cone::Cone( Texture* t ){
    length = 1;
    texture = t;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Cone Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Cone::~Cone(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Cone redraw
 *    Handles actually drawing the Cone object with the OpenGL
 *    framework.
 *
 *    The Cone is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Cone::redraw(){
	if( texture != NULL )
		textureRedraw();
	else{
		
	    glPushMatrix();
	        glColor3f( colors[0]->r, colors[0]->g, colors[0]->b );
	        glTranslatef( xLoc, yLoc, zLoc );
	        glRotatef( angle + 270.0, dxRot, dyRot, dzRot );
	        glScalef( xSize, ySize, zSize );
	        material->activate();
            glColorMaterial( GL_FRONT_AND_BACK, GL_SPECULAR );
	        glutSolidCone( 0.5, 1, 50, 50 );
	    glPopMatrix();
	    glutSwapBuffers();
	}
}

void Cone::textureRedraw(){
	float x2yAspect = texture->getWidth() / (float)texture->getHeight();
	glMatrixMode( GL_MODELVIEW );

	texture->enable();
	// glBegin( GL_TRIANGLE_FAN );
	glTranslatef( xLoc, yLoc, zLoc );
    glRotatef( angle + 270.0, dxRot, dyRot, dzRot );
    // glScalef( xSize, ySize, zSize );
    glutSolidCone( 0.5, 1, 50, 50 );
	glTranslatef( 0.0, 0.0, -50.0 );
    float yscale = 1.75f;
    float xscale = yscale * x2yAspect;
    glScalef( xscale * xSize, yscale * ySize, 2.0 );

    // glEnd();
	texture->disable();
	glutSwapBuffers();
}