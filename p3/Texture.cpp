/*
 * Texture.cpp -- An object-oriented revision of David Henry's texture loader
 *
 * Created by Matt Plumlee 10/26/2008
 *
 * Edited by Dan Bergeron 10/08/2012
 *    - added accessors
 *
 * Notice for use of Henry's code:
 * Copyright( c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files( the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

extern "C"
{
   #include <jpeglib.h>
}
#include "Texture.h"

//------------------ Constructors ------------------------------------

/** Initialize texture id

 */
Texture::Texture()
{
   textureID = 0;  // avoid compiler warning
   width = height = 0;
   format = 0;
   internalFormat = 0;
   texels = NULL;

   // Generate 1 texture; its id is returned in 2nd parameter
   //   If 1st parameter > 1, must pass a reference to an array
   //   of ints.
   glGenTextures( 1, &textureID );
}

//---------------------------------------------------------------------

/** Release texture id
 */

Texture::~Texture()
{
    glDeleteTextures( 1, &textureID );

}

//---------------------- accessors ------------------------------------
GLuint  Texture::getId()     { return textureID; }
GLsizei Texture::getWidth()  { return width; }
GLsizei Texture::getHeight() { return height; }

//---------------------------------------------------------------------

/** Open the file specified and read in the info
 */

bool Texture::readJPEGfromFile( std::string filename )
{
   FILE *fp = NULL;
   struct jpeg_decompress_struct cinfo;
   struct jpeg_error_mgr jerr;

   JSAMPROW scanline;  // JSAMPROW

   /* Open image file */
   fp = fopen( filename.c_str(), "rb" );
   if ( !fp )
   {
      fprintf( stderr, "error: couldn't open \"%s\"!\n", filename.c_str());
      return false;
   }

   /* Create and configure decompressor */
   jpeg_create_decompress( &cinfo );
   cinfo.err = jpeg_std_error( &jerr );
   jpeg_stdio_src( &cinfo, fp );

   /*
   * NOTE: this is the simplest "readJpegFile" function. There
   * is no advanced error handling.  It would be a good idea to
   * setup an error manager with a setjmp/longjmp mechanism.
   *
   * In this function, if an error occurs during reading the JPEG
   * file, the libjpeg aborts the program.
   * See jpeg_mem.c (or RTFM) for an advanced error handling which
   * prevent this kind of behavior( http://tfc.duke.free.fr)
   */

   /* Read header and prepare for decompression */
   jpeg_read_header( &cinfo, TRUE );
   jpeg_start_decompress( &cinfo );

   /* Initialize image's member variables */
   width = cinfo.image_width;
   height = cinfo.image_height;
   internalFormat = cinfo.num_components;
   if ( cinfo.num_components == 1 )
      format = GL_LUMINANCE;
   else
      format = GL_RGB;
   int lineSize = width * internalFormat;
   texels = new GLubyte[ height * lineSize ];

   /* Extract each scanline of the image */
   for( int i = 0; i < height; ++i )
   {
      scanline = &texels[( ( height - (i + 1) ) * lineSize ) ];
      jpeg_read_scanlines( &cinfo, &scanline, 1);
   }
   /* Finish decompression and release memory */
   jpeg_finish_decompress( &cinfo );
   jpeg_destroy_decompress( &cinfo );

   fclose( fp );
   return true;
}

//---------------------------------------------------------------------

/** Open the file specified and read in the info
 */

bool Texture::loadJPEG( std::string filename )
{
   if ( !readJPEGfromFile( filename ))
      return false;

   if ( texels )
   {
      /* Generate texture */
      glBindTexture( GL_TEXTURE_2D, textureID );

      /* Setup some parameters for texture filters and mipmapping */
      glTexParameteri( GL_TEXTURE_2D, 
                       GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                       // GL_TEXTURE_MIN_FILTER, GL_NEAREST );
                       // GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, 
                       GL_TEXTURE_MAG_FILTER, GL_LINEAR );

      gluBuild2DMipmaps( GL_TEXTURE_2D, internalFormat, width, height,
			              format, GL_UNSIGNED_BYTE, texels );

      /* OpenGL makes its own copy of texture data, so we can release it now. */
      delete []texels;
      return true;
   }
   return false;
}

//---------------------------------------------------------------------

/** Enable the texture to be mapped to vertices
 */
void Texture::enable()
{
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, textureID );
}

//---------------------------------------------------------------------

/** Stop mapping this texture to vertices
 */

void Texture::disable()
{
   glDisable( GL_TEXTURE_2D );
}
