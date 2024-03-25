#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>

class Observer;

class Subject {
public:
    virtual void attach(std::weak_ptr<Observer> obs) = 0;
    virtual void detach(std::weak_ptr<Observer> obs) = 0;
    virtual void notifyObservers(std::weak_ptr<Observer> obs, bool attached) = 0;
};

#endif