/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Box.cpp - A class implementation representing a 3D box object
 *    for OpenGL
 *
 * Jonathan Nappi
 * October 3, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Box.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No Arg Box Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Box::Box(){
    length = 1;
    texture = NULL;
    material = NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Texture enabled Box Constructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Box::Box( Texture* t ){
    length = 1;
    texture = t;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Box Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Box::~Box(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Box redraw
 *    Handles actually drawing the Box object with the OpenGL
 *    framework.
 *
 *    The Box is defined by positions relative to it's location
 *    stored in the points array.
 *
 *    The scale factor applies to the relative offset of each coordinate
 *    from the origin (xLoc,yLoc,zLoc)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Box::redraw(){
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
            glutSolidCube( length );
        glPopMatrix();
        glutSwapBuffers();
    }
}

void Box::textureRedraw(){
    float x2yAspect = texture->getWidth() / (float)texture->getHeight();
    float yscale = 1.75f;
    float xscale = yscale * x2yAspect;
    float x0 = -1.0, y0 = -1, x1 = 1, y1 = 1, z0 = 1;
    float face[6][4][3] =  { {{x0, y0, z0}, {x1, y0, z0}, {x1, y1, z0}, {x0, y1, z0}},    //front
                        {{x0, y1, -z0}, {x1, y1, -z0}, {x1, y0, -z0}, {x0, y0, -z0}},    //back
                        {{x1, y0, z0}, {x1, y0, -z0}, {x1, y1, -z0}, {x1, y1, z0}},        //right 
                        {{x0, y0, z0}, {x0, y1, z0}, {x0, y1, -z0}, {x0, y0, -z0}},        //left 
                        {{x0, y1, z0}, {x1, y1, z0}, {x1, y1, -z0}, {x0, y1, -z0}},        //top 
                        {{x0, y0, z0}, {x0, y0, -z0}, {x1, y0, -z0}, {x1, y0, z0}}        //bottom 
                            };
    glMatrixMode( GL_MODELVIEW );
    texture->enable();
    for( int i = 0; i < 6; i++ ){
        glBegin( GL_QUADS );
            glTexCoord2f(0.0, 0.0); glVertex3fv ( face[i][0] );     
            glTexCoord2f(1.0, 0.0); glVertex3fv ( face[i][1] );    
            glTexCoord2f(1.0, 1.0); glVertex3fv ( face[i][2] );
            glTexCoord2f(0.0, 1.0); glVertex3fv ( face[i][3] );
        glEnd();
    }
    glTranslatef( xLoc, yLoc, zLoc );
    glRotatef( angle, dxRot, dyRot, dzRot );
    glScalef( xscale * xSize, yscale * ySize, 1.0 );
    glutSolidCube( length );
    texture->disable();
    glutSwapBuffers();
}
