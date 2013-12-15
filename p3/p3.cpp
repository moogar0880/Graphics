#include "Texture.h"
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "ControlPanel.h"
#include "Box.h"
#include "Sphere.h"
#include "Cone.h"
#include "Donut.h"

float angle = 0; //for the spinning panel
float replication = 1.0f;  // # copies of texture on quad in each direction
float offset = 0.0f;       // offset of map origin as % of quad in x and y
int   deltaRep = 1;
int   revolution = 0;       // how many complete revolutions have been made.

int   stepsPer90 = 180;         // # steps to make to cover 90 degrees
int   stepsLeft  = stepsPer90; // # steps left for current 90 deg segment
float deltaAng   = 90.0f / stepsPer90;
float deltaOff   = 0.15;
bool  spin       = true;

float x2yAspect = 1.0f; // keep texture mapping consistent with input image
Texture *myTexture, *myTexture2;
// Pointer to Scenes collection will be passed to the ControlPanel
std::vector<Scene*> allScenes;     // keep ptrs to all scenes
std::vector<Object3D*> someObjects;

//---------------------------------------------------------------------
void initGL(){
    /* Initialize OpenGL */
    glClearColor( 0.4f, 0.4f, 0.5f, 1.0f );
    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );

    //This is in case the image has some transparency
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    //lighting set up
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_COLOR_MATERIAL);
}

//----------------- makeBox ----------------------------
/**
 *  A convenience function to create a Box with a uniform scale,
 *    a specified color, and at 0,0,0.
 */
Box* makeBox( float scale, Color* c = new Color( 1, 0, 0) ){
    Box* box = new Box( myTexture );
    box->setColor( c );
    box->setLocation( 0, 0, 0 );
    box->setSize( scale, scale, scale );
    return box;
}
//----------------- makeBall ----------------------------
Sphere* makeBall( float scale, Color* c = new Color() ){
    Sphere* sp = new Sphere( myTexture );
    sp->setLocation( 0, 0, 0 );
    sp->setSize( scale, scale, scale );
    sp->setColor( c );
    return sp;
}

void buildMultiTextureScene( void ){
    Box* box = new Box( myTexture2 );
    box->setLocation( 2, 0, 0 );
    box->setSize( 1, 1, 1 );
    someObjects.push_back( box );

    Box* box2 = new Box( myTexture );
    box->setLocation(0, 0, 0);
    box->setSize(1, 1, 1);
    someObjects.push_back( box2 );

    Scene* scene = new Scene("Multi Texture Scene");
    scene->addObject(box);
    scene->addObject(box2);
    allScenes.push_back(scene);
}

//--------------------- appInit ------------------------
void appInit( void ){
    initGL();

    if( myTexture2 != NULL )
        buildMultiTextureScene();

    Cone* c = new Cone();
    c->setLocation( 0, 0, 0 );
    c->setSize( 1, 1, 1 );

    Material* m = new Material();
    m->setEmissive( true );
    c->setMaterial( m );
    someObjects.push_back( c );

    Scene* cScene = new Scene( "Cone Scene with Emissive enabled");
    cScene->addObject( c );
    allScenes.push_back( cScene );

    Sphere* s = new Sphere();
    s->setLocation( 0, 0, 0 );
    s->setSize( 1, 1, 1 );

    m = new Material();
    m->setDiffuse( true );
    s->setMaterial( m );
    someObjects.push_back( s );

    Scene* sScene = new Scene( "Sphere Scene with Diffuse enabled");
    sScene->addObject( s );
    allScenes.push_back( sScene );

    Box* b = new Box();
    b->setLocation( 0, 0, 0 );
    b->setSize( 1, 1, 1 );

    m = new Material();
    m->setSpecular( true );
    b->setMaterial( m );
    someObjects.push_back( b );

    Scene* bScene = new Scene( "Box Scene with Specular enabled");
    bScene->addObject( b );
    allScenes.push_back( bScene );

    Box* box1 = makeBox( 1, new Color( 1, 0, 1 ));  //unit magenta box
    someObjects.push_back( box1 );  // save it for future use

    Scene* boxScene = new Scene( "Box Scene with Texture" );
    boxScene->addObject( box1 );
    allScenes.push_back( boxScene );

    Donut* donut = new Donut( myTexture );
    donut->setColor( new Color( 1, 0, 1 ) );
    donut->setLocation( 0, 0, 0 );
    donut->setSize( 1.0, 1.0, 1.0 );
    donut->setRotate( 45, 0, 1, 0);
    someObjects.push_back( donut );

    Scene* donutScene = new Scene( "Donut Scene" );
    donutScene->addObject( donut );
    allScenes.push_back( donutScene );

    Cone* cone = new Cone( myTexture );
    cone->setColor( new Color( 1, 0, 1 ) );
    cone->setLocation( 0, 0, 0 );
    cone->setSize( 1.0, 1.0, 1.0 );
    someObjects.push_back( cone );

    Scene* coneScene = new Scene( "Cone Scene" );
    coneScene->addObject( cone );
    allScenes.push_back( coneScene );

    Sphere* sp = makeBall( 1, new Color( 0.8, 0.8, 0 )); // yellow ball
    someObjects.push_back( sp );  // save it for future use

    Scene* ballScene = new Scene( "Ball Scene" );
    ballScene->addObject( sp );
    allScenes.push_back( ballScene );
}

//---------------------------------------------------------------------
int main( int argc, char *argv[] ){
    if ( argc < 2 ){
        std::cerr << "usage: " << argv[0] << " <filename>\n" << std::endl;
        return 1;
    }
    int mainWin;
    std::cerr << argc << std::endl;
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 1024, 768 );
    mainWin = glutCreateWindow( "p3" );

    myTexture = new Texture();
    myTexture->loadJPEG( argv[1] );
    myTexture2 = NULL;
    if( argc == 3 ){
        myTexture2 = new Texture();
        myTexture2->loadJPEG( argv[2] );
    }
    
    x2yAspect = myTexture->getWidth() / (float) myTexture->getHeight();

    appInit(  );   // set up scenes to be viewed

    ControlPanel* controls = ControlPanel::getInstance();

    controls->initialize( "Control Panel", mainWin );
    controls->setSceneWorld( &allScenes );

    glutMainLoop( );

    return 0;
}
