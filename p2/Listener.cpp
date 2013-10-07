/**
 * Listener.cpp - An abstract class that can be registered with an observable
 *                so it can be informed of changes in the observable.
 * 
 * mdp
 * September 7, 2008
 */

#include "Observable.h"

//------------------ Constructors ------------------------------------
/** Register ourselves with the observable so we get notified.
 */
Listener::Listener( Observable *observable )
{
    observed = observable;
    if ( observed )
        observed->attach( this );
}

//------------------ Destructor ------------------------------------
/** Remove ourselves from the obervable's list!
 */
Listener::~Listener()
{
    if ( observed )
        observed->detach( this );
}
