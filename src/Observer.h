#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual void update(std::weak_ptr<Observer> obs, bool attached) = 0;
};

#endif 