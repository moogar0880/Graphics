/**
 * CS 770/870 p0, Fall 2013
 *
 * Code heavily derived from Chapter 2 examples of Hill & Kelley textbook
 *
 * @author Jonathan Nappi
 * @date   September 6, 2013
 */

// define std:vector to be included
#include <vector>

// glut.h includes GL.h and glu.h
#include <GL/glut.h>

#include "Quad.h"
#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"

// A vector of all the shapes we will create
std::vector<Shape*>  shapes;

// window size parameters
int windowWidth  = 800;
int windowHeight = 600;

//----------------------< appInit --------------------
 void appInit(void)
 {
    glClearColor( 1.0, 1.0, 1.0, 0.0 );  // set the bg color to a bright white
    glColor3f( 0.0f, 0.0f, 0.0f );       // set the drawing color to black

    // Set up a projection specification that will "see" objects
    //    defined in a coordinate system plane and "window" that
    //    approximates the size of the window.
    //
    glMatrixMode( GL_PROJECTION );       // set up matrices- to be explained
    glLoadIdentity();                    //                  to be explained
    gluOrtho2D( 0.0, windowWidth, 0.0, windowHeight );// to be explained

    // Create 3 triangle objects, with different locations/sizes/colors
    //    add them to the shapes array.

    // Triangles
    Triangle* tri = new Triangle();
    tri->setLocation( 10, 50 );
    tri->setColor( 0, 1, 1 );
    shapes.push_back( tri );

    tri = new Triangle();
    tri->setLocation( 70, 50 );
    tri->setColor( 1, 0, 1 );
    tri->setSize( 2, 2 );
    shapes.push_back( tri );

    tri = new Triangle();
    tri->setLocation( 300, 50 );
    shapes.push_back( tri );

    // Rectangles - Teal
    Rectangle* rec = new Rectangle(100.0,200.0);
    rec->setColor( 0, 1, 1 );
    rec->setLocation(200,200);
    shapes.push_back( rec );

    rec = new Rectangle(100.0,200.0);
    rec->setColor( 0, 1, 1 );
    rec->setLocation(400,200);
    shapes.push_back(rec);

    rec = new Rectangle(100.0,200.0);
    rec->setColor( 0, 1, 1 );
    rec->setLocation(600,200);
    shapes.push_back(rec);

    // Quads - Green
    Quad* qua = new Quad(new Point(200.0,200.0),
                         new Point(100.0,200.0),
                         new Point(0.0,  400.0),
                         new Point(250.0,350.0));
    qua->setColor( 0, 1, 0 );
    qua->setLocation(450,200);
    shapes.push_back( qua );

    qua = new Quad(new Point(200.0,200.0),
                   new Point(200.0,100.0),
                   new Point(400.0,  0.0),
                   new Point(350.0,250.0));
    qua->setColor( 0, 1, 0 );
    qua->setBorderColor( 1, 1, 0 );
    qua->setLocation(450, 2);
    shapes.push_back( qua );


    // Polygons - Blue
    Polygon* pol = new Polygon(5,
                               0.0,   0.0,
                               100.0, 0.0,
                               100.0, 200.0,
                               0.0,   200.0,
                               200.0, 200.0);
    pol->setColor( 0, 0, 1 );
    pol->setBorderColor( 1, 0, 1 );
    pol->setLocation(10,375);
    shapes.push_back( pol );

    pol = new Polygon(6,
                      0.0,   0.0,
                      100.0, 0.0,
                      100.0, 200.0,
                      150.0, 175.0,
                      200.0, 200.0,
                      250.0, 200.0);
    pol->setLocation(400,15);
    shapes.push_back( pol );
}

//------------------------ redraw -----------------
// the redraw function
void redraw( void )
{
   glClear( GL_COLOR_BUFFER_BIT );     // clear the screen

   // create a vector iterator to access the Shapes in the "shapes" vector
   std::vector<Shape*>::iterator it;
   for ( it = shapes.begin(); it < shapes.end(); it++ )
       (*it)->redraw();

   glFlush();                     // send all output to display
}

//------------------------ main ----------------------
int main( int argc, char **argv )
{
   glutInit( &argc, argv );                       // initialize toolkit
   glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); // set the display mode
   glutInitWindowSize( windowWidth, windowHeight );
   glutInitWindowPosition( 100, 150 );           // window position on screen
   glutCreateWindow( "p0" );                     // open the screen window
   glutDisplayFunc( redraw );                    // register redraw function
   appInit();
   glutMainLoop();                               // go into a perpetual loop
}
