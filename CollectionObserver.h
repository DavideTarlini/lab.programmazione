#ifndef COLLECTIONOBSERVER_H
#define COLLECTIONOBSERVER_H

#include <iostream>

class CollectionObserver {
    public:
        CollectionObserver() = default;
        ~CollectionObserver() = default;
        void updateCollectionSize(const std::string& collectionName, int info);
        bool operator==(const CollectionObserver& obs) const;
};


/* Implementation */
void CollectionObserver::updateCollectionSize(const std::string& collectionName, int info) {
    std::cout << "Collection '" << collectionName << "' size updated: " << info << std::endl;
}

bool CollectionObserver::operator==(const CollectionObserver& obs) const{
    return this == &obs;
}

#endif