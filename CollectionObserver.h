#ifndef COLLECTIONOBSERVER_H
#define COLLECTIONOBSERVER_H

#include <iostream>
#include "Observer.h"

class CollectionObserver : public Observer {
    public:
        CollectionObserver() = default;
        ~CollectionObserver() = default;
        void update(const std::string& collectionName, int size) override;
        bool operator==(const CollectionObserver& obs) const;
};


/* Implementation */
void CollectionObserver::update(const std::string& collectionName, int size) {
    std::cout << "Collection '" << collectionName << "' size updated: " << size << std::endl;
}

bool CollectionObserver::operator==(const CollectionObserver& obs) const{
    return this == &obs;
}

#endif