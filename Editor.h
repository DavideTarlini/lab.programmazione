#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>
#include "Collection.h"

class Editor {
    private: 
        std::vector<std::shared_ptr<Collection>> collections;
        std::vector<std::shared_ptr<Note>> notes;

    public:
        Editor() = default;
        ~Editor() = default;
        std::weak_ptr<Collection> addCollection(const std::string &name);
        void removeCollection(std::weak_ptr<Collection> collection);
        std::weak_ptr<Observer> addObserverToCollection(std::weak_ptr<Collection> collection);
        void removeObserverToCollection(std::weak_ptr<Observer>, std::weak_ptr<Collection> collection);
        std::weak_ptr<Note> createNote(const std::string &title);
        void addNoteToCollection(std::weak_ptr<Note> note, const std::string &name);
        void removeNotefromCollection(std::weak_ptr<Note> note, const std::string &name);
        void editNote(std::weak_ptr<Note> note) const;
        void deleteNote(std::weak_ptr<Note> note);
};

std::weak_ptr<Collection> Editor::addCollection(const std::string& name) {
    auto c = std::make_shared<Collection>(name);
    collections.push_back(c);

    return c;
}

void Editor::removeCollection(std::weak_ptr<Collection> collection) {
    auto c = collection.lock();
    if(c){
        auto it = std::find(collections.begin(), collections.end(), c);
        if (it != collections.end()) {
            collections.erase(it);
        }
    }
}

std::weak_ptr<Observer> Editor::addObserverToCollection(std::weak_ptr<Collection> collection) {
    auto obs = std::make_shared<CollectionObserver>(CollectionObserver());
    auto c = collection.lock();
    if(c){
        c->attach(obs);
    }

    return obs;
}

void Editor::removeObserverToCollection(std::weak_ptr<Observer> obs, std::weak_ptr<Collection> collection) {
    auto c = collection.lock();
    auto o = obs.lock();
    if(c && o){
        c->detach(o);
    }
}

std::weak_ptr<Note> Editor::createNote(const std::string& title) {
    auto n = std::make_shared<Note>(title, std::string(""));
    notes.push_back(n);

    return n;
}

void Editor::addNoteToCollection(std::weak_ptr<Note> note, const std::string &name) {
    for(auto c: collections) {
        if(c->getName() == name){
            c->addNote(note);
            break;
        }
    }
}

void Editor::removeNotefromCollection(std::weak_ptr<Note> note, const std::string &name) {
    for(auto c: collections) {
        if(c->getName() == name){
            c->removeNote(note);
            break;
        }
    }
}

void Editor::editNote(std::weak_ptr<Note> note) const {
    auto n = note.lock();
    if(n) {    
        if(n->isLocked())
            return;
        
        std::cout << "Enter text. Type 'END' on a new line to finish: \n";

        std::string noteContent;
        while (true) {
            std::string line;
            std::getline(std::cin, line);
            if (line == "END") {
                break;
            }
            noteContent += line + "\n";
        }

        if(noteContent != std::string("END")){
            n->setText(noteContent);
        }

        std::string newTitle;
        std::cout << "Enter a new title or type END: ";
        std::getline(std::cin, newTitle);

        if(newTitle != std::string("END")){
            n->setTitle(newTitle);
        }
    }
}

void Editor::deleteNote(std::weak_ptr<Note> note) {
    auto n = note.lock();
    if(n) {
        if(n->isLocked())
            return;

        for(auto c: collections) {
            c->removeNote(n);
        }

        auto it = std::find(notes.begin(), notes.end(), n);
        if (it != notes.end())
            notes.erase(it);
    }
}

#endif