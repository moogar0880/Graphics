/**
 * Observable.h - An abstract class that tells registered listeners
 *                when a change has occurred.  Implements the Subject
 *                part of the Observer pattern.
 * 
 * mdp
 * September 7, 2008
 */
#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>
#include "Listener.h"

class Observable
{
    public:
	
        Observable();
        virtual ~Observable();

        virtual bool attach( Listener* );
        virtual bool detach( Listener* );
        virtual void notify(int info, int x, int y);

    private:
        std::vector<Listener*> listeners;
};

#endif /*OBSERVABLE_H_*/
