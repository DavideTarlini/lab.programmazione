#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual void update(bool attached) = 0;
};

#endif 