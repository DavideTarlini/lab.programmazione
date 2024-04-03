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
    protected:
        std::string name;
        std::vector<std::weak_ptr<Note>> notes;
        std::vector<std::weak_ptr<Observer>> observers;

    public:
        Collection(const std::string& name);
        ~Collection() = default;
        const std::string getName() const;
        void addNote(const std::weak_ptr<Note> note);
        void removeNote(const std::weak_ptr<Note> note);
        const std::weak_ptr<Note> getNote(const std::string &name) const;
        void attach(const std::weak_ptr<Observer> observer) override;
        void detach(const std::weak_ptr<Observer> observer) override;
        void notifyObservers(bool noteAdded) override;
        const int numOfObservers() const;
        bool operator==(const Collection& obs) const;
};

Collection::Collection(const std::string& name) : name(name) {}

const std::string Collection::getName() const {
    return name;
}

void Collection::addNote(const std::weak_ptr<Note> note) {
    auto n = note.lock();
    if(n && !n->inCollection()){
        notes.push_back(note);
        notifyObservers(true);
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
            s_note->setInCollection(false);
        }

        notifyObservers(false);
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

void Collection::attach(const std::weak_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Collection::detach(const std::weak_ptr<Observer> observer) {
    auto working_observer = observer.lock();
    if(working_observer){
        int i = 0;
        for(auto obs: observers){
            auto o = obs.lock();
            if(o && o.get() == working_observer.get())
                break;
            
            i++;
        }

        auto it = std::next(observers.begin(), i);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
}

void Collection::notifyObservers(bool noteAdded) {
    for(auto o: observers){
        auto obs = o.lock();
        if(obs)
            obs->update(noteAdded);
    }
}

const int Collection::numOfObservers() const {
    return observers.size();
}

bool Collection::operator==(const Collection& obs) const {
    return this == &obs;
}

#endif