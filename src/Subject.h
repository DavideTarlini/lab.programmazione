#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <memory>


class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> obs) = 0;
    virtual void detach(std::shared_ptr<Observer> obs) = 0;
    virtual void notifyObserver(std::shared_ptr<Observer> observer, bool attached) = 0;
};

#endif