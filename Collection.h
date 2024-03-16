#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "CollectionObserver.h"
#include "Note.h"
#include "Subject.h"


class Collection : public Subject {
    private:
        std::string name;
        std::vector<std::weak_ptr<Note>> notes;
        std::vector<std::shared_ptr<Observer>> observers;

    public:
        Collection(const std::string& name);
        ~Collection() = default;
        const std::string getName() const;
        void addNote(const std::weak_ptr<Note> note);
        void removeNote(const std::weak_ptr<Note> note);
        void attach(const std::shared_ptr<Observer> observer) override;
        void detach(const std::shared_ptr<Observer> observer) override;
        void notifyObserver(int info) override;
};


/* Implementation */

Collection::Collection(const std::string& name) : name(name) {}

const std::string Collection::getName() const {
    return name;
}

void Collection::addNote(const std::weak_ptr<Note> note) {
    notes.push_back(note);
    notifyObserver(notes.size());
}

void Collection::removeNote(const std::weak_ptr<Note> note) {
    int i = 0;
    bool found = false;
    std::vector<std::weak_ptr<Note>>::iterator it;
    for(auto n: notes) {
        auto s_n = n.lock();
        auto s_note = note.lock();

        if(*s_n == *s_note){
            found = true;
            it = std::next(notes.begin(), i);
            break;
        }

        i++;
    }
    
    if (found) {
        notes.erase(it);
        notifyObserver(notes.size());
    }
}

void Collection::attach(const std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Collection::detach(const std::shared_ptr<Observer> observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Collection::notifyObserver(int newSize) {
    for (auto observer : observers) {
        observer->update(name, newSize);
    }
}

#endif