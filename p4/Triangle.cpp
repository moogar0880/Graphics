/**
 * Triangle.cpp - a class implementation representing a triangle object
 *           in OpenGL
 * 
 * rdb
 * October 2013: derived from C++ basicOpenGL demo to us glsl
 * 
 */
#include "opengl.h"
#include "Triangle.h"

extern bool vaoSupported;
bool shadersBuilt = false;
GLuint shaderProgram;

//------------- forward/extern references ----------------------
extern int checkGLerror( const char*, bool quit = false );
//------------- constructor -----------------------
Triangle::Triangle(){
    float dxDefault[] = { -0.25, 0.25, 0.0 };
    float dyDefault[] = { 0.0, 0.0, 0.5 };
    nPoints = 3;
    
    for ( int i = 0; i < nPoints; i++ ){
        relPoints[ i ] = point2( dxDefault[ i ], dyDefault[ i ] );
    }
    bind();
}

//------------- destructor -----------------------
Triangle::~Triangle(){}

//------------------ public methods -------------------------------
/**
 * @override
 * set the location of the object to the x,y position defined by the args
 */
void Triangle::setLocation( float x, float y ){
    float dx = x - loc.x;
    float dy = y - loc.y;
    for ( int i = 0; i < nPoints; i++ ){
        relPoints[i].x += dx;
        relPoints[i].y += dy;
    }
    loc.x = x;
    loc.y = y;
    bind();
}
/**
 * The shape is complete (for now); send its data to the gpu
 */
void Triangle::bind() {
    if ( vaoSupported )
        makeBuffers();
    if ( !shadersBuilt )
        buildShaders();
}

bool vaoMessagePrinted = false;
//------------------------------ makeBuffers -----------------------
/**
 *  create VertaxArrayObject and VertexBufferObject
 */
void Triangle::makeBuffers(){
    // ---- set up to transfer points to gpu
    // 1. Create a vertex array object (VAO)
    GLuint vPosId[ 1 ];
    glGenVertexArrays( 1, vPosId );
    GLuint gle = checkGLerror( "Triangle:GenVertexArrays" );
    if ( gle ){  // checkGLerror returns 0 if no error occurred
        std::cerr << "************ VAO not supported *****************\n";
        //vaoSupported = false;
        std::cerr << "************ Ignoring test; using VAO anyway ****\n";
    }
    //else
    {
        if ( !vaoMessagePrinted )
            std::cerr << "*********** Using Vertex Array Objects ***********\n";
        vaoMessagePrinted = true;
        vertexArrayId = vPosId[ 0 ];    // save in instance variable
        glBindVertexArray( vertexArrayId );
        std::cerr << "Binding " << vertexArrayId << std::endl;
        // 2. Create and initialize a buffer object
        GLuint buffer[ 1 ];
        glGenBuffers( 1, buffer );
        bufferId = buffer[ 0 ];         // save in instance variable
        glBindBuffer( GL_ARRAY_BUFFER, bufferId );
        glBufferData( GL_ARRAY_BUFFER, sizeof(relPoints), relPoints,
                                                           GL_STATIC_DRAW );
        // Initialize the vertex position attribute from the vertex shader
        GLuint loc = glGetAttribLocation( shaderProgram, "vPosition" );
        glEnableVertexAttribArray( loc );
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        
        GLuint pmv = glGetAttribLocation( shaderProgram, "projXmv" );
        glEnableVertexAttribArray( pmv );
        glVertexAttribPointer( pmv, 2, GL_DOUBLE, GL_FALSE, 0, BUFFER_OFFSET(0));
    }
}

//------------------ buildShaders --------------------------
void Triangle::buildShaders(){
    // std::cerr << "buildShaders " << std::endl;
    // Load shaders and use the resulting shader program
    // shaderProgram = angel::makeShaderProgram( "passThru.vsh", "flat.fsh" );
    
    // glUseProgram( shaderProgram );
    // shadersBuilt = true;
}

//----------------------- sendXformToShader ------------------------------
void Triangle::sendXformToShader(){
    //---- need to get Proj * ModelView matrix into the shader for
    //  transforming all vertices.
    //
    // We'll do that getting the MV matrix and multiplying it in the
    //   Proj matrix stack (after pushing)
    GLfloat modelview[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
    
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glMultMatrixf( modelview );   // P = P*MV
    
    GLfloat PtimesMV[16];
    glGetFloatv( GL_PROJECTION_MATRIX, PtimesMV );
    
    glPopMatrix();   // and clean up Proj matrix stack
    
    //--- now push the composite into a uniform var in vertex shader
    GLint matLoc = glGetUniformLocation( shaderProgram, "projXmv" );
    glUniformMatrix4fv( matLoc, 1, false, PtimesMV );
}

//------------- redraw ---------------------------
void Triangle::redraw(){
    sendXformToShader();
    
    // For now we'll color entire polygon the same using a uniform variable
    GLint colorLoc = glGetUniformLocation( shaderProgram, "rdbcolor" );
    glUniform4fv( colorLoc, 1, color ); // there is 1 array/struct
    
    if ( vaoSupported ){
        std::cerr<< "<Triangle.redraw() VAO: " << vertexArrayId << "\n";
    
        glBindVertexArray( vertexArrayId ); // bind vao to buffer data
        glDrawArrays( GL_TRIANGLES, 0, nPoints );
        glBindVertexArray( 0 );    // unbind this vao from buffer
    }
    else{
        std::cerr<< "<Triangle.redraw() no VAO: \n";
        glBegin( GL_POLYGON );
            // The triangle is defined by positions relative to its location
            // stored in the dx and dy arrays. The scale factor applies to the
            // relative offset of each coordinate from the origin (which is
            // xLoc, yLoc )
            for ( int i = 0; i < nPoints; i++ ){
                glVertex2f( loc.x + relPoints[ i ].x * xSize,
                       loc.y + relPoints[ i ].y * ySize );
            }
        glEnd();
    }
}
