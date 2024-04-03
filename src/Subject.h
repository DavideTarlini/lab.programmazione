#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>

class Observer;

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(const std::weak_ptr<Observer> obs) = 0;
    virtual void detach(const std::weak_ptr<Observer> obs) = 0;
    virtual void notifyObservers(bool msg) = 0;
};

#endif