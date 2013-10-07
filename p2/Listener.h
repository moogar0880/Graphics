/**
 * Listener.h - An abstract class that can be registered with an observable
 *              so it can be informed of changes in the observable.
 * 
 * mdp
 * September 7, 2008
 */
#ifndef LISTENER_H_
#define LISTENER_H_

class Observable; //declare the class, we'll include it in the .cpp file

class Listener
{
    public:
        Listener( Observable *observable );
        virtual ~Listener();

        virtual void update( int info, int x, int y ) = 0;

    protected:
        Observable *observed;
};

#endif /*LISTENER_H_*/
