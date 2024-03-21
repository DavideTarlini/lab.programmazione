#ifndef NOTE_H
#define NOTE_H

#include <string>
#include "Subject.h"

class Note : public Subject {
private:
    std::string title;
    std::string text;
    bool locked;
    std::vector<std::shared_ptr<Observer>> collections;

public:
    Note(const std::string& title, const std::string& text);
    ~Note() = default;
    void lock();
    void unlock();
    bool isLocked() const;
    void setTitle(const std::string& newTitle);
    void setText(const std::string& newText);
    const std::string& getTitle() const;
    const std::string& getText() const;
    void attach(const std::shared_ptr<Observer> observer) override;
    void detach(const std::shared_ptr<Observer> observer) override;
    void notifyObserver(const std::shared_ptr<Observer> observer, bool attached) override;
    void removeAllCollections(); 
    bool operator==(const Note& note) const;
};


Note::Note(const std::string& title, const std::string& text)
    : title(title), text(text), locked(false) {}

void Note::lock() {
    locked = true;
}

void Note::unlock() {
    locked = false;
}

bool Note::isLocked() const {
    return locked;
}

void Note::setTitle(const std::string& newTitle) {
    if(!locked)
        title = newTitle;
}

void Note::setText(const std::string& newText) {
    if(!locked)
        text = newText;
}

const std::string& Note::getTitle() const {
    return title;
}

const std::string& Note::getText() const {
    return text;
}

void Note::attach(const std::shared_ptr<Observer> observer) {
    collections.push_back(observer);
    notifyObserver(observer, true);
}

void Note::detach(const std::shared_ptr<Observer> observer) {
    auto it = std::find(collections.begin(), collections.end(), observer);
    if (it != collections.end()) {
        collections.erase(it);
        notifyObserver(observer, false);
    }
}

void Note::notifyObserver(const std::shared_ptr<Observer> observer, bool attached) {
    observer->update(attached);
}

void Note::removeAllCollections() {
    for(auto c: collections) {
        this->detach(c);
    }
}

bool Note::operator==(const Note& note) const{
    return this == &note;
}

#endif