#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note {
private:
    std::string title;
    std::string text;
    bool locked;

public:
    Note(const std::string& title, const std::string& text);
    ~Note() = default;
    void lock();
    void unlock();
    bool isLocked() const;
    void setTitle(std::string& newTitle);
    void setText(std::string& newText);
    const std::string& getTitle() const;
    const std::string& getText() const;
    bool operator==(const Note& note) const;
};


/* Implementation */

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

void Note::setTitle(std::string& newTitle) {
    if(!locked)
        title = newTitle;
}

void Note::setText(std::string& newText) {
    if(!locked)
        title = newText;
}

const std::string& Note::getTitle() const {
    return title;
}

const std::string& Note::getText() const {
    return text;
}

bool Note::operator==(const Note& note) const{
    return (this->getText() == note.getText()) && (this->getTitle() == note.getTitle());
}

#endif