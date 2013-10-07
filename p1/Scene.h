/**
 * Scene.h - a class to keep track of a scene of objects, and
 *           mouse interactions with the screen
 *
 * mdp
 * September 21, 2008
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>
#include <GL/glut.h>
#include "GlutMouseListener.h"
#include "Color.h"

class Shape;

class Scene : public GlutMouseListener{
public:
    //----Singleton Pattern getInstance method----
    static Scene *getInstance();

    //----Methods----
    void addShape( Shape *newShape );
    void remove( int i );
    void clear();
    void current_shape_set( int current );
    void set_boundary_color( Color* c );
    void set_fill_color( Color* c );
    void set_draw_boundary( bool b );
    void set_draw_fill( bool b );
    bool empty();
    Shape* get_most_recent();

protected:
    //----Singleton Pattern parts----
    Scene();
    static Scene *instance;

    //----MouseListener response methods----
    virtual void mousePressed( int button, int x, int y );
    virtual void mouseReleased( int button, int x, int y );
    virtual void mouseMoved( int x, int y );

    //----Callback for redraw and mouse-button menus---
    //Callbacks to register w/ GLUT, and call object-level method
    static void redraw_cb();
    static void processRightButtonMenu_cb( int command );
    enum { EXIT_CMD,
           CLEAR_CMD
         };
    //object-level method for handling callbacks
    void redraw( void );
    void rightButtonMenu( int command );
    void draw_tri(  int x, int y );
    void draw_rect( int x, int y );
    void draw_quad( int x, int y );
    void draw_poly( int x, int y );

    //----Member variables----
    std::vector<Shape*> shapes;
    bool rubberbanding;             //are we currently rubberbanding?
    int rbStartX, rbStartY;         //where is the rubberband starting?
    int current_shape;
    Color *borderColor, *fillColor;
    bool drawBoundary, drawFill;
    int newX, newY;
};

#endif /*SCENE_H_*/
