#ifndef COLLECTION_OBSERVER_H
#define COLLECTION_OBSERVER_H

#include "Observer.h"
#include "Collection.h"

class CollectionObserver : public Observer {
private:
    int observedSize;
    Collection* subject;

public:
    CollectionObserver(Collection* sbj);
    ~CollectionObserver();
    void update() override;
    const int getObservedSize();
};

CollectionObserver::CollectionObserver(Collection* sbj) {
    if(sbj){
        sbj->attach(this);
        subject = sbj; 
        observedSize = sbj->getSize();
    }
}

CollectionObserver::~CollectionObserver() {
    if(subject){
        subject->detach(this); 
    }
}

void CollectionObserver::update() {
    if(subject){
        observedSize = subject->getSize();
    }
}

const int CollectionObserver::getObservedSize() {
    return observedSize;
}

#endif