#ifndef COLLECTION_OBSERVER_H
#define COLLECTION_OBSERVER_H

#include "Observer.h"

class CollectionObserver : public Observer {
private:
    int observedSize = 0;
public:
    CollectionObserver() = default;
    ~CollectionObserver() = default;
    void update(const bool added) override;
    const int getObservedSize();
};

void CollectionObserver::update(const bool added) {
    if(added)
        observedSize++;
    else
        observedSize--;
}

const int CollectionObserver::getObservedSize() {
    return observedSize;
}

#endif