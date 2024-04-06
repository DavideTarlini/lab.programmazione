#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>

class Observer;

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* obs) = 0;
    virtual void detach(Observer* obs) = 0;
    virtual void notifyObservers() const = 0;
};

#endif