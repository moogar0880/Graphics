/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Material.cpp - A class implementation representing the material
 *			properties of an openGL Graphics object
 *
 * Jonathan Nappi
 * October 29, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Material.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No args constructor sets default values
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Material::Material(){
	diffuse = emissive = specular = false;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * MAterial Destructor
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Material::~Material(){}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Material::setDiffuse( bool b ){
	diffuse = b;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Material::setEmissive( bool b ){
	emissive = b;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Material::setSpecular( bool b ){
	specular = b;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Material::activate(){
	GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; 
    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
    GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
    GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
    GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
    GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
    GLfloat blankMaterial[] = {0.0, 0.0, 0.0};
    GLfloat mShininess[] = {128};
	if( diffuse ){
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
    }
    else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
    }
    if( emissive ){
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
    }
    else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
    }
    if( specular ){
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mShininess );
    }
    else{
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blankMaterial);
    }
}