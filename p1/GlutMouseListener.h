/**
 * GlutMouseListener.h - A class that can receive mouse event notifications
 *
 * mdp
 * September 7, 2008
 */
#ifndef GLUTMOUSELISTENER_H_
#define GLUTMOUSELISTENER_H_

#include "Listener.h"
#include <iostream>
#include <GL/glut.h>

class GlutMouseListener : public Listener
{
    public:
        GlutMouseListener();

    protected:
        virtual void mousePressed( int button, int x, int y ) {};
        virtual void mouseReleased( int button, int x, int y ) {};
        virtual void mouseMoved( int x, int y ) {};

    private:
        virtual void update( int info, int x, int y );
};

#endif /*GLUTMOUSELISTENER_H_*/
