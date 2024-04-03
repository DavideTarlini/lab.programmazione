#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(bool msg) = 0;
};

#endif 