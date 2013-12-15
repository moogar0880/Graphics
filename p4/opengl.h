/**
 *   opengl.h 
 *
 *   This file tries to encapsulate in one file all the variations
 *   needed for writing protable OpenGL programs for CS770/870
 *
 *   It includes extra stuff for the early assignments and perhaps
 *   will need to be extended for later assignments.
 *   
 *   Edit it as needed, but submit edited version only after testing
 *   that it works on agate.
 * 
 *   rdb 10/22/13
 */

#ifndef __OPENGL_H__
    #define __OPENGL_H__

    #define GL_GLEXT_PROTOTYPES

    #if defined( __APPLE__ ) // include Mac OS X verions of headers
    #  include <OpenGL/OpenGL.h>
    #  include <GLUT/glut.h>
    #  include <GLUI/glui.h>
    #  define glBindVertexArray glBindVertexArrayAPPLE
    #  define glGenVertexArrays glGenVertexArraysAPPLE
    #elif defined( __WIN32 ) || defined( __WIN64 )
    #  include <windows.h>
    #  include <GL/glut.h>   // glut.h includes gl.h
    #  // not sure if the rest of these are needed, except glext.h probably is
    #  include <GL/glew.h>
    #  include <GL/freeglut.h>
    #  include <GL/freeglut_ext.h>
    #  include <GL/glext.h>
    #else     // assume unix
    #  include <GL/glut.h>   // glut.h includes gl.h
    #  include <GL/glext.h>
    #endif  // __APPLE__
#endif  // __OPENGL_H__

