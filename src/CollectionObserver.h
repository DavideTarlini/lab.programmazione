#ifndef COLLECTION_OBSERVER_H
#define COLLECTION_OBSERVER_H

#include "Observer.h"
#include "Collection.h"

class CollectionObserver : public Observer, std::enable_shared_from_this<CollectionObserver> {
private:
    int observedSize;
    std::weak_ptr<Collection> subject;

public:
    CollectionObserver(std::weak_ptr<Collection> sbj);
    ~CollectionObserver();
    void update() override;
    const int getObservedSize();
};

CollectionObserver::CollectionObserver(std::weak_ptr<Collection> sbj) {
    auto s = sbj.lock();
    if(s){
        s->attach(this);
        subject = sbj; 
        auto s = subject.lock();
        if(s){
            observedSize = s->getSize();
        }
    }
}

CollectionObserver::~CollectionObserver() {
    auto s = subject.lock();
    if(s){
        s->detach(this); 
    }
}

void CollectionObserver::update() {
    auto s = subject.lock();
    if(s){
        observedSize = s->getSize();
    }
}

const int CollectionObserver::getObservedSize() {
    return observedSize;
}

#endif