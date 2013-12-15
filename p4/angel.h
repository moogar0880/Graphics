//////////////////////////////////////////////////////////////////////////////
//
//  --- angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
// 10/18/13 rdb: Edit glut include to distingush Windows from unix
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_H__
#define __ANGEL_H__

//----------------------------------------------------------------------------
//
// --- Include system headers ---
//

#include <cmath>
#include <iostream>
#include <stdio.h>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

//----------------------------------------------------------------------------
//
// --- Include OpenGL header files and helpers ---
//
//   The location of these files vary by operating system.  We've included
//     copies of open-soruce project headers in the "GL" directory local
//     this this "include" directory.
//
// edited by rdb
#include "opengl.h"

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Include our class libraries and constants ---
//

namespace angel
{
    //  Helper function to load vertex and fragment shader files
    GLuint makeShaderProgram( const char* vertexShaderFile,
                             const char* fragmentShaderFile );
    
    //  Defined constant for when numbers are too small to be used in the
    //    denominator of a division operation.  This is only used if the
    //    DEBUG macro is defined.
    const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);
    
    //  Degrees-to-radians constant
    const GLfloat  DegreesToRadians = M_PI / 180.0;
    
}  // namespace angel

#include "vec.h"
#include "mat.h"
//rdb #include "CheckError.h"

#define Print(x)  do { std::cerr << #x " = " << (x) << std::endl; } while(0)

#endif // __ANGEL_H__
