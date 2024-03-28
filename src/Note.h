#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include <memory>

class Note {
private:
    std::string name;
    std::string text;
    bool locked;

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

bool Note::operator==(const Note& note) const{
    return this == &note;
}

#endif