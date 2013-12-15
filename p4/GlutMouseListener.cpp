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
//------------------ mouse event handlers -----------------------------
void GlutMouseListener::mousePressed( int button, int x, int y )
{
   std::cerr << button << "pressed " << x << ", " << y  << std::endl;
};
void GlutMouseListener::mouseReleased( int button, int x, int y )
{
   std::cerr << button << "released " << x << ", " << y  << std::endl;
};
void GlutMouseListener::mouseMoved( int x, int y )
{
   std::cerr << "moved " << x << ", " << y << std::endl;
};


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


