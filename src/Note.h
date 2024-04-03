#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include <memory>

class Collection;

class Note {
private:
    std::string name;
    std::string text;
    bool locked;
    bool inColl;
    void setInCollection(bool in);
    
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
    const bool inCollection() const;
    bool operator==(const Note& note) const;

    friend Collection;
};

Note::Note(const std::string& name, const std::string& text)
    : name(name), text(text), locked(false), inColl(false) {}

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

void Note::setInCollection(bool in) {
    inColl = in;
}

const bool Note::inCollection() const {
    return inColl;
}

bool Note::operator==(const Note& note) const{
    return this == &note;
}

#endif