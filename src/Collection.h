#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Subject.h"
#include "Observer.h"
#include "Note.h"

class Collection : public Subject {
    private:
        std::string name;
        bool important;
        std::vector<std::weak_ptr<Note>> notes;
        std::vector<Observer*> observers;

    public:
        Collection(const std::string& name, const bool isImportant);
        ~Collection() = default;
        std::string getName() const;
        void addNote(const std::weak_ptr<Note> note);
        void removeNote(const std::weak_ptr<Note> note);
        const std::weak_ptr<Note> getNote(const std::string &name) const;
        void attach(Observer* observer) override;
        void detach(Observer* observer) override;
        void notifyObservers() const override;
        int getSize() const;
        int numOfObservers() const;
};

Collection::Collection(const std::string& name, bool isImportant) : name(name), important(isImportant) {}

std::string Collection::getName() const {
    return name;
}

void Collection::addNote(const std::weak_ptr<Note> note) {
    auto n = note.lock();
    if(n && (!n->inCollection() || important)){
        notes.push_back(note);
        notifyObservers();
        if(!important)
            n->setInCollection(true);
    }
}

void Collection::removeNote(const std::weak_ptr<Note> note) {
    auto s_note = note.lock();
    if(s_note){
        int i = 0;
        for(auto n: notes){
            auto s_n = n.lock();
            if(s_n && s_n.get() == s_note.get())
                break;
                
            i++;
        }

        auto it = std::next(notes.begin(), i);
        if (it != notes.end()) {
            notes.erase(it);
            if(!important)
                s_note->setInCollection(false);
        }

        notifyObservers();
    }
}

const std::weak_ptr<Note> Collection::getNote(const std::string &name) const {
    std::weak_ptr<Note> wn;

    for(auto n: notes) {
        auto s_n = n.lock();
        if(s_n && s_n->getName() == name){
            wn = n;
            break;
        }
    }

    return wn;
}

void Collection::attach(Observer* observer) {
    observers.push_back(observer);
}

void Collection::detach(Observer* observer) {
    int i = 0;
    for(auto o: observers){
        if(o && o == observer)
            break;
            
        i++;
    }

    auto it = std::next(observers.begin(), i);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Collection::notifyObservers() const {
    for(auto o: observers){
        if(o)
            o->update();
    }
}

int Collection::getSize() const {
    return notes.size();
}

int Collection::numOfObservers() const {
    return observers.size();
}

#endif