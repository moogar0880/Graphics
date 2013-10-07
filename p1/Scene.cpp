/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Scene.cpp - a class to keep track of a scene of objects, and
 *           mouse interactions with the screen
 *
 * @author Jonathan Nappi
 * @date   September 6, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Scene.h"
#include "Shape.h"
#include "Quad.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Point.h"
#include "GlutMouseSource.h"
#include <GL/glui.h>
#include <stddef.h>
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Class Variables
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Scene *Scene::instance = NULL;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Scene constructor - initalize any values and register GLUI callbacks
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Scene::Scene(){
    rubberbanding = false;
    rbStartX = 0;
    rbStartY = 0;

	GLUI_Master.set_glutDisplayFunc( redraw_cb );   // register redraw function
    glutCreateMenu( processRightButtonMenu_cb );
    glutAddMenuEntry( "Clear scene", CLEAR_CMD );
    glutAddMenuEntry( "Exit", EXIT_CMD );
    //attach current menu to a right-click
    glutAttachMenu( GLUT_RIGHT_BUTTON );

    // Default Values
    current_shape = newX = newY = 0;
    borderColor   = fillColor = new Color(1,0,0);
    drawBoundary  = drawFill = true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Get instance - Return the singleton instance, if one does not exist
 *      then create one
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Scene *Scene::getInstance(){
    if ( !instance )
        instance = new Scene();
    return instance;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add the provided shape to the shapes Vector
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::addShape( Shape *newShape ){
    shapes.push_back( newShape );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Empty the shapes vector, then redraw
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::clear(){
    shapes.clear();
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the current default shape, to be used for knowing which shape
 *      to draw on mousedown
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::current_shape_set( int current ){
    current_shape = current;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the default border color, to be used for shape creation events
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::set_boundary_color( Color* c ){
    borderColor = c;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the default fill color, to be used for shape creation events
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::set_fill_color( Color* c ){
    fillColor = c;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set default border drawing behaviour, to be used for shape creation
 *      events
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::set_draw_boundary(bool b){
    drawBoundary = b;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set default fill drawing behaviour, to be used for shape creation
 *      events
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::set_draw_fill(bool b){
    drawFill = b;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Removes the ith element from the shapes Vector
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::remove(int i){
    if( i <= shapes.size() && !shapes.empty() ){
        shapes.erase(shapes.begin() + i);
        redraw();
    }
    else{
        std::cerr << "No shape at index " << i << std::endl;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Pass control to the class's rightButtonMenu method
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::processRightButtonMenu_cb( int command ){
    getInstance()->rightButtonMenu( command );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle right button menu events
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::rightButtonMenu( int command ){
    switch ( command )
    {
        case EXIT_CMD:
            exit( 0 );
            break;
        case CLEAR_CMD:
            clear();
            break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Redraw callback method passes control to the redraw method
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::redraw_cb(){
    getInstance()->redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Redraw's the current scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::redraw( void ){
    glClear( GL_COLOR_BUFFER_BIT );   // clear the scene

    // create a vector iterator to access the Shapes in the "shapes" vector
    std::vector<Shape*>::iterator it;
    for ( it = shapes.begin(); it < shapes.end(); it++ )
       (*it)->redraw();

    glFlush();		                 // send all output to display
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Start a rubberBand when on LMB down
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::mousePressed( int button, int x, int y ){
    if ( button == GlutMouseSource::MOUSE_BUTTON_LEFT ){
        rubberbanding = GL_TRUE;
        rbStartX = x;
        rbStartY = y;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Disable rubberBand and create default shape on MouseUp
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::mouseReleased( int button, int x, int y ){
    if ( button == GlutMouseSource::MOUSE_BUTTON_LEFT ){
        rubberbanding = GL_FALSE;
        rbStartY = 600 - rbStartY;
        newY = 600 - newY;
        float width  = ( newX - rbStartX ) * 1.0;
        float height = ( newY - rbStartY )* 1.0;
        Shape* newShape;
        if( current_shape == 0 ){
            Point **ps = new Point *[3];
            ps[0] = new Point( rbStartX, rbStartY );
            ps[1] = new Point( rbStartX, newY );
            ps[2] = new Point( newX, newY);
            newShape = new Triangle( ps );
        }
        else if( current_shape == 1 || current_shape == 2 ){
            newShape = new Rectangle( width, height );
            newShape->setLocation( rbStartX, rbStartY );
        }
        else if( current_shape == 3 ){
            Polygon* poly = new Polygon();
            poly->setSize( newX - rbStartX, newY - rbStartY );
            newShape->setLocation( rbStartX, rbStartY );
        }
        newShape->setColor( fillColor );
        newShape->setBorderColor( borderColor );
        newShape->setDrawBorder( drawBoundary );
        newShape->setDrawFill( drawFill );
        shapes.push_back( newShape );
        redraw();
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Handle drawing the rubberBand
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::draw_rect( int x, int y ){
    int viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    int ySize = viewport[3];

    redraw();
    glColor3f( 0.8f, 0.5f, 0.6f );
    glBegin( GL_LINE_STRIP );
        glVertex2f( rbStartX, ySize - rbStartY );
        glVertex2f( x, ySize - rbStartY );
        glVertex2f( x, ySize - y );
        glVertex2f( rbStartX, ySize - y );
        glVertex2f( rbStartX, ySize - rbStartY );
    glEnd();
    glFlush();
    newX = x;
    newY = y;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return the empty status of the shapes vector
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool Scene::empty( void ){
    return shapes.empty();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return reference to the most recent shape in shapes vector
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Shape* Scene::get_most_recent( void ){
    return shapes.back();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Draw or continue drawing rubberband if rubberbanding is enabled
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Scene::mouseMoved( int x, int y ){
    if ( rubberbanding ){
        draw_rect( x, y );
    }
}
