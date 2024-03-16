#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual void update(const std::string& collectionName, int size) = 0;
};

#endif 