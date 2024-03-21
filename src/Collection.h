#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Note.h"
#include "Observer.h"


class Collection : public Observer {
    private:
        std::string name;
        int size;

    public:
        Collection(const std::string& name);
        ~Collection() = default;
        const std::string getName() const;
        void update(bool attached) override;
        bool operator==(const Collection& obs) const;
};


Collection::Collection(const std::string& name) : name(name), size(0) {}

const std::string Collection::getName() const {
    return name;
}

void Collection::update(bool attached) {
    if(attached)
        size++;
    else
        size--;
}

bool Collection::operator==(const Collection& obs) const {
    return this == &obs;
}

#endif