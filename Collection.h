#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "CollectionObserver.h"
#include "Note.h"


class Collection {
    private:
        std::string name;
        std::vector<Note> notes;
        std::vector<CollectionObserver> observers;

    public:
        Collection(const std::string& name);
        ~Collection() = default;
        void addNote(const Note& note);
        void removeNote(const Note& note);
        void subscribe(const CollectionObserver& observer);
        void unsubscribe(const CollectionObserver& observer);
        void notifyObserver(int info);
};


/* Implementation */

Collection::Collection(const std::string& name) : name(name) {}

void Collection::addNote(const Note& note) {
    notes.push_back(note);
    notifyObserver(notes.size());
}

void Collection::removeNote(const Note& note) {
    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end()) {
        notes.erase(it);
        notifyObserver(notes.size());
    }
}

void Collection::subscribe(const CollectionObserver& observer) {
    observers.push_back(observer);
}

void Collection::unsubscribe(const CollectionObserver& observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Collection::notifyObserver(int newSize) {
    for (CollectionObserver observer : observers) {
        observer.updateCollectionSize(name, newSize);
    }
}

#endif