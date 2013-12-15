/**
 * Material.h - A class representing the material properties of
 *				an openGL object
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include "opengl.h"

class Material
{
public:
    Material();
    virtual ~Material();
    void setDiffuse( bool b );
    void setEmissive( bool b );
    void setSpecular( bool b );
    void activate();

protected:
	bool diffuse, emissive, specular;
};

#endif /*MATERIAL_H_*/
