/**
 * GlutMouseListener.cpp - A class that can receive mouse event notifications
 *
 * mdp
 * September 7, 2008
 */

#include "GlutMouseListener.h"
#include "GlutMouseSource.h"

//------------------ Constructors ------------------------------------
/**
 * Instantiate as a listener that attaches to a GlutMouseSource
 */
GlutMouseListener::GlutMouseListener()
                  : Listener( GlutMouseSource::getInstance() )
{
}

//------------------ other methods -----------------------------------
void GlutMouseListener::update( int info, int x, int y )
{
    switch ( info & GlutMouseSource::MOUSE_ACTION_MASK )
    {
        case GlutMouseSource::MOUSE_BUTTON_DOWN:
            mousePressed( info & GlutMouseSource::MOUSE_BUTTON_MASK, x, y );
            break;
        case GlutMouseSource::MOUSE_BUTTON_UP:
            mouseReleased( info & GlutMouseSource::MOUSE_BUTTON_MASK, x, y );
            break;
        case GlutMouseSource::MOUSE_MOTION:
            mouseMoved(x, y);
            break;
    }
}


