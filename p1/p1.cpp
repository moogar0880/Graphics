/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * CS 770/870 p0, Fall 2013
 *
 * Code heavily derived from Chapter 2 examples of Hill & Kelley textbook
 *
 * @author Jonathan Nappi
 * @date   September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// define std:vector to be included
#include <vector>
// stderr import
#include <iostream>
// glut.h includes GL.h and glu.h
#include <GL/glut.h>
#include "GlutMouseListener.h"
// Shapes
#include "Quad.h"
#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"
// GLUI Libraries
#include "ControlPanel.h"
#include "Scene.h"

// window size parameters
int windowWidth  = 800;
int windowHeight = 600;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle drawing the triangles
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void drawTriangles(void){
  Scene *scene = Scene::getInstance();
  Triangle* tri = new Triangle();
  tri->setLocation( 10, 50 );
  tri->setColor( 0, 1, 1 );
  scene->addShape( tri );

  tri = new Triangle();
  tri->setLocation( 70, 50 );
  tri->setColor( 1, 0, 1 );
  tri->setSize( 2, 2 );
  scene->addShape( tri );

  tri = new Triangle();
  tri->setLocation( 300, 50 );
  scene->addShape( tri );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle drawing the rectangles - default color is teal
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void drawRectangles(void){
  Scene *scene = Scene::getInstance();
  Rectangle* rec = new Rectangle(100.0,200.0);
  rec->setColor( 0, 1, 1 );
  rec->setLocation(200,200);
  scene->addShape( rec );

  rec = new Rectangle(100.0,200.0);
  rec->setColor( 0, 1, 1 );
  rec->setLocation(400,200);
  scene->addShape( rec );

  rec = new Rectangle(100.0,200.0);
  rec->setColor( 0, 1, 1 );
  rec->setLocation(600,200);
  scene->addShape( rec );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle drawing the quads - default color is green
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void drawQuads(void){
  Scene *scene = Scene::getInstance();
  Quad* qua = new Quad(new Point(200.0,200.0),
                       new Point(100.0,200.0),
                       new Point(0.0,  400.0),
                       new Point(250.0,350.0));
  qua->setColor( 0, 1, 0 );
  qua->setLocation(450,200);
  scene->addShape( qua );

  qua = new Quad(new Point(200.0,200.0),
                 new Point(200.0,100.0),
                 new Point(400.0,  0.0),
                 new Point(350.0,250.0));
  qua->setColor( 0, 1, 0 );
  qua->setBorderColor( 1, 1, 0 );
  qua->setLocation(450, 2);
  scene->addShape( qua );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle drawing the polygons - default color is blue
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void drawPolygons(void){
  Scene *scene = Scene::getInstance();
  Polygon* pol = new Polygon(5,
                             0.0,   0.0,
                             100.0, 0.0,
                             100.0, 200.0,
                             0.0,   200.0,
                             200.0, 200.0);
  pol->setColor( 0, 0, 1 );
  pol->setBorderColor( 1, 0, 1 );
  pol->setLocation(10,375);
  scene->addShape( pol );

  pol = new Polygon(6,
                    0.0,   0.0,
                    100.0, 0.0,
                    100.0, 200.0,
                    150.0, 175.0,
                    200.0, 200.0,
                    250.0, 200.0);
  pol->setLocation(400,15);
  scene->addShape( pol );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialize the app
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 void appInit(void){
  glClearColor( 1.0, 1.0, 1.0, 0.0 );  // set the bg color to a bright white
  glColor3f( 0.0f, 0.0f, 0.0f );       // set the drawing color to black
  glPointSize( 4.0 );                 //set the point size to 4 by 4 pixels
  // Set up a projection specification that will "see" objects
  //    defined in a coordinate system plane and "window" that
  //    approximates the size of the window.
  //
  glMatrixMode( GL_PROJECTION );       // set up matrices- to be explained
  glLoadIdentity();                    // to be explained
  gluOrtho2D( 0.0, windowWidth, 0.0, windowHeight );// to be explained

  drawTriangles();
  drawRectangles();
  drawQuads();
  drawPolygons();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Main function for the app
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main( int argc, char **argv ){
  int mainWin;

  glutInit( &argc, argv );                       // initialize toolkit
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); // set the display mode
  glutInitWindowSize( windowWidth, windowHeight );
  glutInitWindowPosition( 100, 150 );           // window position on screen
  mainWin = glutCreateWindow( "p1" );           // open the screen window
  // Now draw the picture and wait for events
  appInit();

  std::cerr << "back from appInit\n";

  GlutMouseListener mouseListener;

  //create a GLUI control panel window (code adapted from GLUI 2.0 manual)
  ControlPanel* controls = ControlPanel::getInstance();
  controls->initialize( "Control Panel", mainWin );

  /** Register the Idle callback with GLUI (instead of with GLUT) **/
  GLUI_Master.set_glutIdleFunc( 0 );

  /** Now call the regular GLUT main loop **/
  glutMainLoop();                               // go into a perpetual loop
}
