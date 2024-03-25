#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include <memory>
#include "Subject.h"
#include "Observer.h"

class Note : public Subject {
private:
    std::string name;
    std::string text;
    bool locked;
    std::vector<std::weak_ptr<Observer>> collections;

public:
    Note(const std::string& name, const std::string& text);
    ~Note() = default;
    void lock();
    void unlock();
    bool isLocked() const;
    void setName(const std::string& newName);
    void setText(const std::string& newText);
    const std::string& getName() const;
    const std::string& getText() const;
    int numOfCollections() const;
    void attach(std::weak_ptr<Observer> observer) override;
    void detach(std::weak_ptr<Observer> observer) override;
    void notifyObservers(std::weak_ptr<Observer> obs, bool attached) override;
    void removeCollections();
    bool operator==(const Note& note) const;
};

Note::Note(const std::string& name, const std::string& text)
    : name(name), text(text), locked(false) {}

void Note::lock() {
    locked = true;
}

void Note::unlock() {
    locked = false;
}

bool Note::isLocked() const {
    return locked;
}

void Note::setName(const std::string& newName) {
    if(!locked)
        name = newName;
}

void Note::setText(const std::string& newText) {
    if(!locked)
        text = newText;
}

const std::string& Note::getName() const {
    return name;
}

const std::string& Note::getText() const {
    return text;
}

int Note::numOfCollections() const{
    return collections.size();
}

void Note::attach(std::weak_ptr<Observer> observer) {
    collections.push_back(observer);
    notifyObservers(observer, true);
}

void Note::detach(std::weak_ptr<Observer> observer) {
    auto working_observer = observer.lock();
    if(working_observer){
        int i = 0;
        for(auto obs: collections){
            auto o = obs.lock();
            if(o && o.get() == working_observer.get())
                break;
            
            i++;
        }

        auto it = std::next(collections.begin(), i);
        if (it != collections.end()) {
            notifyObservers(observer, false);
            collections.erase(it);
        }
    }
}

void Note::notifyObservers(std::weak_ptr<Observer> obs, bool attached) {
    for(auto c: collections){
        auto sc = c.lock();
        if(sc)
            sc->update(obs, attached);
    }
}

void Note::removeCollections() {
    while(collections.size() > 0){
        detach(collections.at(0));
    }
}

bool Note::operator==(const Note& note) const{
    return this == &note;
}

#endif