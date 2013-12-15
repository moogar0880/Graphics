/**
* CS 770/870 Assignment2, Fall 2012
*
* Code heavily derived from Chapter 2 examples of Hill & Kelley textbook
*
* @author rdb
* @date   August 2008
*-------------------------------------------
* 09302012 - changed a lot by Can Xiong for A2 graphics
* Implemetation:
* 1. CanScene has multiple copies of single-component object wrappers like
*    cone, cube, cylinder, sphere, teapot and torus.
* 2. CanScene is composed by three hierarchically defined Object3D classes
*    instances such as teatable, flowerlight and tree.
* 3. Interactive modification of the view
*    a. turn on/off the light;
*    b. turn on/off drawing coordinate;
*    c. -- disabled The origin teatable can be translated, rotated and scaled;
*    d. switch among perspective, frustum and ortho projections;
*     e. change the parameters of the viewing by these spinners;
*    f. you can also set the lookat parameters as well as you can zoom in and out.
*    g. mouse actions--press left button and move horizontally( check left or right of objects )
*                    --press middle button and move vertically( zoom in/out )
*     h. Next CanScene button ( 4 scenes )
*/

#include <cmath>
#include <vector>

//compatible with windows and linux operating systems
// glut.h includes GL.h and glu.h
#if ( defined( __CYGWIN__ ) || defined( __linux__ ) )
   #include <GL/glut.h>
#else
   #include <glut.h>
#endif

#include "GlutMouseListener.h"

#include "Box.h"
#include "Sphere.h"

// My Shapes
#include "Cone.h"
#include "Donut.h"
// My Composites
#include "Eye.h"
#include "Hat.h"
#include "Head.h"
#include "Clown.h"
#include "Snowman.h"

#include "ControlPanel.h"
#include "Scene.h"

int windowWidth  = 640;//816;
int windowHeight = 480;//488;

// Pointer to Scenes collection will be passed to the ControlPanel
std::vector<Scene*> allScenes;     // keep ptrs to all scenes

// For testing, we'll keep pointers to a bunch of created objects in a vector
//    also. This makes it easy to just select previously created objects
//    for multiple scenes, or to copy them and change transformations.
std::vector<Object3D*> someObjects;

//----------------- forward declarations ----------------
void redraw();
void makeSimpleScenes();
void makeMultiObjectScenes();

//----------------- makeBox ----------------------------
/**
 *  A convenience function to create a Sphere with a uniform scale,
 *    a specified color, and at 0,0,0.
 */
Box* makeBox( float scale, Color* c = new Color( 1, 0, 0) ){
    Box* box = new Box();
    box->setColor( c );
    box->setLocation( 0, 0, 0 );
    box->setSize( scale, scale, scale );
    return box;
}
//----------------- makeBall ----------------------------
Sphere* makeBall( float scale, Color* c = new Color() ){
    Sphere* sp = new Sphere();
    sp->setLocation( 0, 0, 0 );
    sp->setSize( scale, scale, scale );
    sp->setColor( c );
    return sp;
}
//--------------------- appInit ------------------------
void appInit( void ){
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );// set bg to a black
    glClearDepth( 1.0 );                   // clears depth buffer
    glEnable( GL_DEPTH_TEST );             // Enable depth testing
    glShadeModel( GL_SMOOTH );             // Enable smooth color shading
    glEnable( GL_NORMALIZE );              // Make all surface normals unit len
    glEnable( GL_COLOR_MATERIAL );         // Current color used for material

    //lighting set up
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    //Set lighting intensity and color
    GLfloat ambientLight[] = {1, 1, 0.4, 0.5};
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );

    //Set the light position
    GLfloat lightPosition[] = {-1, 1, 1, 0};
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );

    makeSimpleScenes();  // make scenes with at least 1 example of each Object3D
    makeMultiObjectScenes();
}

//------------------------- makeSimpleScenes --------------------------
/**
 *  make all one object scenes
 */
void makeSimpleScenes(){
    Snowman* snow = new Snowman();
    snow->setLocation( 0, 0, 0 );
    snow->setSize( 1, 1, 1 );
    someObjects.push_back( snow );

    Scene* snowScene = new Scene();
    snowScene->addObject( snow );
    allScenes.push_back( snowScene );

    Clown* clown = new Clown();
    clown->setLocation( 0, 0, 0 );
    clown->setSize( 1,1,1 );
    someObjects.push_back( clown );

    Scene* clown1Scene = new Scene();
    clown1Scene->addObject( clown );
    allScenes.push_back( clown1Scene );

    Head* head = new Head();
    head->setLocation( 0, 0, 0 );
    head->setSize( 1, 1, 1 );
    someObjects.push_back( head );

    Scene* headScene = new Scene();
    headScene->addObject( head );
    allScenes.push_back( headScene );

    Hat* hat = new Hat();
    // hat->setColor( new Color( 1, 0, 1 ) );
    hat->setLocation( 0, 0, 0 );
    hat->setSize( 0.5, 0.5, 0.5 );
    someObjects.push_back( hat );

    Scene* hat1Scene = new Scene();
    hat1Scene->addObject( hat );
    allScenes.push_back( hat1Scene );

    Eye* eye = new Eye();
    eye->setColor( new Color( 1, 0, 0 ) );
    eye->setLocation( 0, 1, 1 );
    eye->setSize( 0.5, 0.5, 0.5 );
    eye->setRotate( 45, 1, 0, 0 );
    someObjects.push_back( eye );

    Scene* eye1Scene = new Scene();
    eye1Scene->addObject( eye );
    allScenes.push_back( eye1Scene );

    Donut* donut = new Donut();
    donut->setColor( new Color( 1, 0, 1 ) );
    donut->setLocation( 0, 0, 0 );
    donut->setSize( 1.0, 1.0, 1.0 );
    donut->setRotate( 45, 0, 1, 0);
    someObjects.push_back( donut );

    Scene* donut1Scene = new Scene();
    donut1Scene->addObject( donut );
    allScenes.push_back( donut1Scene );

    Cone* cone = new Cone();
    cone->setColor( new Color( 1, 0, 1 ) );
    cone->setLocation( 0, 0, 0 );
    cone->setSize( 1.0, 1.0, 1.0 );
    someObjects.push_back( cone );

    Scene* cone1Scene = new Scene();
    cone1Scene->addObject( cone );
    allScenes.push_back( cone1Scene );

    Box* box1 = makeBox( 1, new Color( 1, 0, 1 ));  //unit magenta box
    someObjects.push_back( box1 );  // save it for future use

    Scene* box1Scene = new Scene();
    box1Scene->addObject( box1 );
    allScenes.push_back( box1Scene );

    Box* box2 = makeBox( 0.25, new Color( 0, 1, 1 )); // smaller cyan box
    box2->setRotate( 45, 0, 0, 1 );
    someObjects.push_back( box2 );  // save it for future use

    Scene* box2Scene = new Scene();
    box2Scene->addObject( box2 );
    allScenes.push_back( box2Scene );

    Sphere* sp = makeBall( 0.5, new Color( 0.8, 0.8, 0 )); // yellow ball
    someObjects.push_back( sp );  // save it for future use

    Scene* ballScene = new Scene();
    ballScene->addObject( sp );
    allScenes.push_back( ballScene );
}

//------------------------- makeSimpleScenes --------------------------
/**
 *  make all one object scenes
 */
void makeMultiObjectScenes(){
    Scene* multi1 = new Scene();
    Object3D* box = new Box( *(Box*)(someObjects[ 5 ]) );
    box->setLocation( 1, 0, 0 );
    box->setSize( 0.4, 0.4, 0.1 );
    multi1->addObject( box );

    box = new Box( *(Box*)(someObjects[ 6 ]) );
    box->setLocation( -1, 0, 0 );
    multi1->addObject( box );

    allScenes.push_back( multi1 );

}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
//rdb void main( int argc, char **argv )
int main( int argc, char **argv ){
    int mainWin;

    glutInit( &argc, argv );                    // initialize glut

    // Display mode is single-buffer, uses RGB, and has a depth buffer
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize( windowWidth, windowHeight );
    glutInitWindowPosition( 100, 150 );   // set window position on screen
    mainWin = glutCreateWindow( "p3" );   // open the screen window

    std::cerr << "Main window id: " << mainWin << "\n";
    appInit();   // set up scenes to be viewed

    // set up interaction
    GlutMouseListener mouseListener;

    //create a GLUI control panel window ( code adapted from GLUI 2.0 manual )
    ControlPanel* controls = ControlPanel::getInstance();

    controls->initialize( "Control Panel", mainWin );
    controls->setSceneWorld( &allScenes );
    controls->getInitValues();

    /** Register the Idle callback with GLUI ( instead of with GLUT ) **/
    GLUI_Master.set_glutIdleFunc( 0 );

    /** Now call the regular GLUT main loop **/
    glutMainLoop();                        // go into a perpetual loop
}
