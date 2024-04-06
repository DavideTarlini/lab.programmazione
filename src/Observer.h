#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

#endif 