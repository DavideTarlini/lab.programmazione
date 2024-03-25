#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>
#include <iostream>
#include "Collection.h"
#include "Note.h"

class Editor {
    private: 
        std::vector<std::shared_ptr<Collection>> collections;
        std::vector<std::shared_ptr<Note>> notes;

    public:
        Editor() = default;
        ~Editor() = default;
        std::weak_ptr<Collection> addCollection(const std::string& name);
        void removeCollection(const std::string& name);
        std::weak_ptr<Collection> getCollection(const std::string& name) const;
        std::weak_ptr<Note> createNote(const std::string& name);
        void addNoteToCollection(const std::string& noteName, const std::string& collectionName);
        void removeNotefromCollection(const std::string& noteName, const std::string& collectionName);
        void editNoteName(const std::string& currentName, const std::string& newName) const;
        void editNoteText(const std::string& name, const std::string& newText) const;
        void deleteNote(const std::string& name);
        std::weak_ptr<Note> getNote(const std::string& name) const;
        int numOfCollections() const;
        int numOfNotes() const;
};

std::weak_ptr<Collection> Editor::addCollection(const std::string& name) {
    auto c = std::make_shared<Collection>(name);
    collections.push_back(c);

    return c;
}

void Editor::removeCollection(const std::string& name) {
    std::shared_ptr<Collection> coll;
    int i = 0;
    for(auto c: collections){
        if(name == c->getName()){
            coll = c;
            break;
        }

        i++;
    }

    auto it = std::next(collections.begin(), i);
    if (it != collections.end()) {
        for(auto n: notes){
            n->detach(coll);
        }

        auto it = std::next(collections.begin(), i);
        collections.erase(it);
    }
}

std::weak_ptr<Collection> Editor::getCollection(const std::string& title) const{
    std::weak_ptr<Collection> wc;

    for(auto c: collections) {
        if(c->getName() == title){
            wc = c;
            break;
        }
    }

    return wc;
}

std::weak_ptr<Note> Editor::createNote(const std::string& name) {
    auto n = std::make_shared<Note>(name, std::string(""));
    notes.push_back(n);

    return n;
}

void Editor::addNoteToCollection(const std::string& noteName, const std::string& collectionName) {
    auto n = getNote(noteName).lock();

    if(n){
        for(auto c: collections) {
            if(c->getName() == collectionName){
                n->attach(c);
                break;
            }
        }
    }
}

void Editor::removeNotefromCollection(const std::string& noteName, const std::string& collectionName) {
    auto n = getNote(noteName).lock();

    if(n){
        for(auto c: collections) {
            if(c->getName() == collectionName){
                n->detach(c);
                break;
            }
        }
    }
}

void Editor::editNoteName(const std::string& currentName, const std::string& newName) const {
    auto note = getNote(currentName).lock();
    if(!note || note->isLocked())
        return;

    note->setName(newName);
}

void Editor::editNoteText(const std::string &name, const std::string &newText) const {
    auto note = getNote(name).lock();
    if(!note || note->isLocked())
        return;

    note->setText(newText);
}

void Editor::deleteNote(const std::string& name) {
    auto note = getNote(name).lock();
    if(note->isLocked())
        return;

    note->removeCollections();

    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end())
        notes.erase(it);
}

std::weak_ptr<Note> Editor::getNote(const std::string& name) const{
    std::weak_ptr<Note> wn;

    for(auto n: notes) {
        if(n->getName() == name){
            wn = n;
            break;
        }
    }

    return wn;
}

int Editor::numOfCollections() const {
    return collections.size();
}

int Editor::numOfNotes() const {
    return notes.size();
}
#endif