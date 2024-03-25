#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Observer.h"


class Collection : public Observer {
    private:
        std::string name;
        int size;

    public:
        Collection(const std::string& name);
        ~Collection() = default;
        const std::string getName() const;
        const int getSize() const;
        void update(std::weak_ptr<Observer> obs, bool attached) override;
        bool operator==(const Collection& obs) const;
};

Collection::Collection(const std::string& name) : name(name), size(0) {}

const std::string Collection::getName() const {
    return name;
}

const int Collection::getSize() const {
    return size;
}

void Collection::update(std::weak_ptr<Observer> obs, bool attached) {
    auto s_obs = obs.lock();
    if(s_obs && s_obs.get() == this){
        if(attached)
            size++;
        else
            size--;
    }
}

bool Collection::operator==(const Collection& obs) const {
    return this == &obs;
}

#endif