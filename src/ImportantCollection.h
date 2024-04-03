#ifndef IMPORTANT_COLLECTION_H
#define IMPORTANT_COLLECTION_H

#include "Collection.h"

class ImportantCollection : public Collection{
public:
    ImportantCollection() : Collection(std::string("Important Notes")) {};
    ~ImportantCollection() = default;
    void addNote(const std::weak_ptr<Note> note);
};

void ImportantCollection::addNote(const std::weak_ptr<Note> note) {
    auto n = note.lock();
    if(n){
        notes.push_back(note);
        notifyObservers(true);
    }
}

#endif