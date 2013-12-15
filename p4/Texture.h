/*
 * Texture.h -- Object-oriented version of David Henry's texture loader
 *
 * Created by Matt Plumlee 10/26/2008
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "opengl.h"

class Texture //could derive this from Addressable eventually...
{
    public:
        Texture();
        ~Texture();

        GLuint  getId();
        GLsizei getWidth();
        GLsizei getHeight();

        void enable();
        void disable();

        bool loadJPEG( std::string filename );

    protected:
        bool readJPEGfromFile( std::string filename );

        GLuint  textureID;
        GLsizei width, height;
        GLenum  format;
        GLint   internalFormat;
        GLubyte *texels;
};

#endif
