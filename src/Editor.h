#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>
#include <iostream>
#include "Collection.h"

class Editor {
    private: 
        std::vector<std::shared_ptr<Collection>> collections;
        std::vector<std::shared_ptr<Note>> notes;

    public:
        Editor() = default;
        ~Editor() = default;
        std::weak_ptr<Collection> addCollection(const std::string &name);
        void removeCollection(const std::shared_ptr<Collection> collection);
        std::weak_ptr<Note> createNote(const std::string &title);
        void addNoteToCollection(std::shared_ptr<Note> note, const std::string &name);
        void removeNotefromCollection(std::shared_ptr<Note> note, const std::string &name);
        void editNote(std::shared_ptr<Note> note) const;
        void deleteNote(std::shared_ptr<Note> note);
};

std::weak_ptr<Collection> Editor::addCollection(const std::string& name) {
    auto c = std::make_shared<Collection>(name);
    collections.push_back(c);

    return c;
}

void Editor::removeCollection(const std::shared_ptr<Collection> collection) {
    for(auto n: notes) {
        n->detach(collection);
    }

    auto it = std::find(collections.begin(), collections.end(), collection);
    if (it != collections.end()) {
        collections.erase(it);
    }
}

std::weak_ptr<Note> Editor::createNote(const std::string& title) {
    auto n = std::make_shared<Note>(title, std::string(""));
    notes.push_back(n);

    return n;
}

void Editor::addNoteToCollection(std::shared_ptr<Note> note, const std::string &name) {
    for(auto c: collections) {
        if(c->getName() == name){
            note->attach(c);
            break;
        }
    }
}

void Editor::removeNotefromCollection(std::shared_ptr<Note> note, const std::string &name) {
    for(auto c: collections) {
        if(c->getName() == name){
            note->detach(c);
            break;
        }
    }
}

void Editor::editNote(std::shared_ptr<Note> note) const {  
    if(note->isLocked())
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
        note->setText(noteContent);
    }
    
    std::string newTitle;
    std::cout << "Enter a new title or type END: ";
    std::getline(std::cin, newTitle);

    if(newTitle != std::string("END")){
        note->setTitle(newTitle);
    }
}

void Editor::deleteNote(std::shared_ptr<Note> note) {
    if(note->isLocked())
        return;

    note->removeAllCollections();

    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end())
        notes.erase(it);
}

#endif