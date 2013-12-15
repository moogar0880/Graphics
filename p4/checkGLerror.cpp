/**
 *  checkGLerrors
 *          This is a utility function to simplify the checking and
 *          reporting of OpenGL errors.
 *  If an error has occurred, the function prints an error message to 
 *     standard error.
 *  The first parameter is an identification string
 *  If the 2nd parameter is true, the function terminates execution
 *  
 *  If no error occurred, 0 is returned, 
 *     else the OpenGL error code is returned.
 *
 * Based on code from Bailey and Cunningham text, "Graphics Shaders"
 * Extensions
 *  1. added parameters
 *           to identify context of the call
 *           to specify process termination if desired
 *  2. added loop, since OpenGL has independent multiple error flags;
 *     if 2 or more occur on same operation, only 1 is returned and cleared.
 *     The loop insures all are identified and cleared.
 *
 * rdb 11/01/13
 */

#include "opengl.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

int checkGLerror( const char* src, bool endit = false ){
    int errCount = 0;
    GLuint gle = glGetError();
    while ( gle != GL_NO_ERROR ){
        std::stringstream msg;
        msg << "**** GL error **** " << src << ": ";
        switch ( gle ){
            case GL_INVALID_ENUM: msg << "Invalid enum"; break;
            case GL_INVALID_VALUE: msg << "Invalid value"; break;
            case GL_INVALID_OPERATION: msg << "Invalid operation"; break;
                //case GL.GL_STACK_OVERFLOW: msg = "Stack overflow"; break;
                //case GL.GL_STACK_UNDERFLOW: msg = "Stack underflow"; break;
            case GL_OUT_OF_MEMORY: msg << "Out of memory"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: 
                 msg << "Bad frame buf op"; break;
            default: msg << "Unknown error " << gle; break;
        }
        std::cerr <<  msg.str() << std::endl;
        errCount++;
        gle = glGetError();
    }
    if ( errCount > 0 && endit )
        exit( gle );
    return errCount;
}
