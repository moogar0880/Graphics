/**
 * GlutMouseSource.cpp - A class that tells registered listeners when
 *                       the user has moved the mouse or changed a
 *                       button state.
 *
 * mdp
 * September 7, 2008
 */

#include "GlutMouseSource.h"
#include <GL/glut.h>
#include <GL/glui.h>

//------------------ Class variables ---------------------------------
GlutMouseSource *GlutMouseSource::instance = (GlutMouseSource*) NULL;

//------------------ Constructors ------------------------------------
/**
 * Register our callbacks with GLUT
 */
GlutMouseSource::GlutMouseSource(){
    GLUI_Master.set_glutMouseFunc( mouseButtonCallback );
    glutMotionFunc( mouseMotionCallback );
    GLUI_Master.set_glutMenuStatusFunc( menuStatusCallback );
}

//------------------ Destructor ------------------------------------
GlutMouseSource::~GlutMouseSource(){
    glutMouseFunc( NULL );
    glutMotionFunc( NULL );
    instance = NULL;
}

//------------------ public class methods --------------------------
/**
 * Return the singleton instance.  If it does not exist, create one.
 */
GlutMouseSource* GlutMouseSource::getInstance(){
    if ( !instance )
        instance = new GlutMouseSource();
    return instance;
}

//------------------- other methods -------------------------------
/**
 * Notify all listeners about a button state change
 */
void GlutMouseSource::mouseButtonCallback( int button, int state, int x, int y ){
    int info = button;
    if ( state == GLUT_DOWN ) //add mouse action flag
        info |= MOUSE_BUTTON_DOWN;
    else
        info |= MOUSE_BUTTON_UP;
    instance->notify( info, x, y );
}

//-----------------------------------------------------------------
/**
 * Notify all listeners about a mouse motion change
 */
void GlutMouseSource::mouseMotionCallback( int x, int y ){
    int info = MOUSE_MOTION; //add mouse action flag
    instance->notify( info, x, y );
}

//-----------------------------------------------------------------
/** Notify all listeners about a mouse button state change, as
 *  caused by the menu passed.
 */
void GlutMouseSource::menuStatusCallback( int state, int x, int y ){
    if ( state == GLUT_MENU_IN_USE ){
        int info = ( glutGetMenu() + 1 ) | MOUSE_BUTTON_DOWN; //&&&just a hack to test!!
        instance->notify( info, x, y );
    }
}
