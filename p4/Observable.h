/**
 * Observable.h - An abstract class that tells registered listeners when a
 *  change has occurred.  Implements the Subject part of the Observer pattern.
 * 
 * @author Carmen St. Jean (crr8, carmen@cs.unh.edu)
 *         Taken from Observable.h of demo3 by Dan Bergeron.
 *
 * UNH CS 870, fall 2012
 *
 * History
 *  10/07/2012: Took class from demo3.
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

        virtual bool attach(Listener *);
        virtual bool detach(Listener *);
        virtual void notify(int info, int x, int y);

    private:
        std::vector<Listener *> listeners;
};

#endif /*OBSERVABLE_H_*/
